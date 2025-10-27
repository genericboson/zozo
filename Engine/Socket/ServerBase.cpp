#include "PCH.h"

#include <boost/exception/all.hpp>

#include "ServerBase.h"

#include "BoostTcpSocket.h"

namespace GenericBoson
{
	mysql::pool_params ServerBase::GetDbPoolParams(
		std::string_view hostname,
		uint16_t         port,
		std::string_view username, 
		std::string_view password,
		std::string_view dbname)
	{
		mysql::pool_params params;
		params.server_address.emplace_host_and_port(hostname.data());
		params.username = username;
		params.password = password;
		params.database = dbname;
		//params.thread_safe = true;

		return params;
	}

	mysql::connect_params ServerBase::GetDbParams(
		std::string_view hostname,
		uint16_t         port,
		std::string_view username,
		std::string_view password,
		std::string_view dbname)
	{
		mysql::connect_params params;
		params.server_address.emplace_host_and_port(hostname.data());
		params.username = username;
		params.password = password;
		params.database = dbname;
		params.multi_queries = true;

		return params;
	}

	ServerBase::ServerBase(int32_t port)
		: 
		m_networkThreadPool{ std::thread::hardware_concurrency() * 2 },
		m_listeningPort{ port },
		m_workGuard{ m_ioContext.get_executor() },
		m_strand{ make_strand(m_networkThreadPool.get_executor()) }
	{
	}

	bool ServerBase::Start()
	{
		try
		{
			m_pAcceptor = std::make_unique<asio::ip::tcp::acceptor>(
				m_ioContext,
				boost::asio::ip::tcp::endpoint(
					boost::asio::ip::tcp::v4(), m_listeningPort));
		}
		catch (const boost::exception& e)
		{
			ERROR_LOG("Exception occured in making acceptor. what - {}", boost::diagnostic_information(e));
			return false;
		}

		INFO_LOG("LobbyServer started ( port - {} )", m_listeningPort);

		Accept();

		m_pIoThread = std::make_unique<std::jthread>([&]() { m_ioContext.run(); });

		m_pDbConn = std::make_unique<mysql::any_connection>(m_ioContext);
		auto [err] = m_pDbConn->async_connect(GetDbParams(
			"127.0.0.1",
			3306,
			"root",
			"1234",
			"zozo_lobby"), asio::as_tuple(asio::use_future)).get();

		if (err != boost::system::errc::success)
		{
			ERROR_LOG("DB connection failed. err - {}({})", err.value(), err.message());
			return false;
		}

		return true;
	}

	void ServerBase::Stop()
	{
		m_isRunning = false;
		m_ioContext.stop();
	}

	bool ServerBase::IsRunning() const
	{
		return m_isRunning;
	}

	awaitable<void> ServerBase::Listen()
	{
		auto ReadLoop = [this](std::shared_ptr<BoostTcpSocket> pSocket) -> awaitable<void>
			{
				auto WriteLoop = [this](std::shared_ptr<BoostTcpSocket> pSocket) -> awaitable<void>
					{
						while (m_isRunning)
						{
							if (!co_await pSocket->Write())
								break;
						}
					};

				co_spawn(co_await this_coro::executor, WriteLoop(pSocket), detached);
				while (m_isRunning)
				{
					if (!co_await pSocket->Read())
						break;
				}
			};

		while (m_isRunning)
		{
			auto socket = co_await m_pAcceptor->async_accept(use_awaitable);

			auto pSocket = std::make_shared<BoostTcpSocket>(std::move(socket));
			auto pActor = CreateActor(pSocket);
			pSocket->Initialize(pActor);

			if (!pActor->Initialize())
			{
				co_return;
			}

			pActor->OnAccepted();

			co_spawn(m_strand, ReadLoop(pSocket), detached);
		}
	}

	void ServerBase::Accept()
	{
		auto CallListen = [this]() -> awaitable<void>
			{
				return Listen();
			};

		co_spawn(m_ioContext, CallListen, detached);
	}
}