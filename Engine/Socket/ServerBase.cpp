#include "PCH.h"

#include <filesystem>

#include <boost/dll/runtime_symbol_info.hpp>
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

	std::optional<pt::ptree> ServerBase::ReadIni()
	{
		const auto& targetPath = std::filesystem::current_path();
		INFO_LOG("ReadIni target path : {}", targetPath.string());

		boost::filesystem::path executablePath = boost::dll::program_location();

		auto iniPath = std::format("{}.{}", (executablePath.parent_path() / executablePath.stem()).string(), "ini");

		pt::ptree iniPt;
		pt::ini_parser::read_ini(iniPath, iniPt);
		
		return iniPt;
	}

	bool ServerBase::InitializeConnection()
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

		Accept();

		m_pDbConn = std::make_unique<mysql::any_connection>(m_ioContext);
		auto [err] = m_pDbConn->async_connect(GetDbParams(
			m_dbIp,
			m_dbPort,
			m_dbAccount,
			m_dbPassword,
			m_dbMainSchema), asio::as_tuple(asio::use_future)).get();

		if (err != boost::system::errc::success)
		{
			ERROR_LOG("DB connection failed. err - {}({})", err.value(), err.message());
			return false;
		}

		return true;
	}

	bool ServerBase::AfterReadIni()
	{
		return InitializeConnection();
	}

	bool ServerBase::Start()
	{
		if (!ReadIni())
			return false;

		m_pIoThread = std::make_unique<std::jthread>([&]() { m_ioContext.run(); });

		return AfterReadIni();
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

	asio::awaitable<void> ServerBase::Listen()
	{
		auto ReadLoop = [this](std::shared_ptr<BoostTcpSocket> pSocket) -> asio::awaitable<void>
			{
				auto WriteLoop = [this](std::shared_ptr<BoostTcpSocket> pSocket) -> asio::awaitable<void>
					{
						while (m_isRunning)
						{
							if (!co_await pSocket->Write())
								break;
						}
					};

				asio::co_spawn(co_await asio::this_coro::executor, WriteLoop(pSocket), asio::detached);
				while (m_isRunning)
				{
					if (!co_await pSocket->Read())
						break;
				}
			};

		while (m_isRunning)
		{
			auto socket = co_await m_pAcceptor->async_accept(asio::use_awaitable);

			auto pSocket = std::make_shared<BoostTcpSocket>(std::move(socket));
			auto pActor = CreateActor(pSocket);
			pSocket->Initialize(pActor);

			if (!pActor->Initialize())
			{
				co_return;
			}

			pActor->OnAccepted();

			asio::co_spawn(m_strand, ReadLoop(pSocket), asio::detached);
		}
	}

	void ServerBase::Accept()
	{
		auto CallListen = [this]() -> asio::awaitable<void>
			{
				return Listen();
			};

		asio::co_spawn(m_ioContext, CallListen, asio::detached);
	}

	asio::io_context& ServerBase::GetIoContextRef()
	{
		return m_ioContext;
	}
}