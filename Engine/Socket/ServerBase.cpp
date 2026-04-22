#include "PCH.h"

#include <filesystem>

#include <boost/dll/runtime_symbol_info.hpp>
#include <boost/exception/all.hpp>

#include "ServerBase.h"

#include "BoostTcpSocket.h"
#include "DB/DBManager.h"
#include "EnvironmentVariable.h"

namespace GenericBoson
{
	ServerBase::ServerBase(int32_t port)
		: 
		m_networkThreadPoolSize{ std::thread::hardware_concurrency() * 2 },
		m_listeningPort{ port },
		m_workGuard{ m_ioContext.get_executor() }
	{
	}

	std::optional<pt::ptree> ServerBase::ReadIni()
	{
		const auto& targetPath = std::filesystem::current_path();
		INFO_LOG("ReadIni target path : {}", targetPath.string());

		boost::filesystem::path executablePath = boost::dll::program_location();

		auto iniPath = std::format("{}.{}", (executablePath.parent_path() / executablePath.stem()).string(), "ini");

		pt::ptree iniPt;

		try
		{
			pt::ini_parser::read_ini(iniPath, iniPt);
		}
		catch (const boost::exception& e)
		{
			ERROR_LOG("Exception occured in read ini. what - {}", boost::diagnostic_information(e));
			return std::nullopt;
		}
		
		return iniPt;
	}

	asio::awaitable<bool> ServerBase::InitializeConnection()
	{
		m_pAcceptor = std::make_unique<asio::ip::tcp::acceptor>(
			m_ioContext,
			boost::asio::ip::tcp::endpoint(
				boost::asio::ip::tcp::v4(), m_listeningPort));

		Accept();

		if (!DBManager::GetInstance()->Initialize(m_ioContext))
		{
			ERROR_LOG("DBManager initialization failed.");
			co_return false;
		}

		INFO_LOG("DBManager initialized successfully.");
		co_return true;
	}

	bool ServerBase::AfterReadIni()
	{
		m_pAcceptor = std::make_unique<asio::ip::tcp::acceptor>(
			m_ioContext,
			boost::asio::ip::tcp::endpoint(
				boost::asio::ip::tcp::v4(), m_listeningPort));

		Accept();

		if (!DBManager::GetInstance()->Initialize(m_ioContext))
		{
			ERROR_LOG("DBManager initialization failed.");
			return false;
		}

		INFO_LOG("DBManager initialized successfully.");
		return true;
	}

	bool ServerBase::Start()
	{
		if (!ReadIni())
			return false;

		m_threads.reserve(m_networkThreadPoolSize);
		for (int32_t i = 0; i < m_networkThreadPoolSize; ++i)
		{
			m_threads.emplace_back( [this]() {
				m_ioContext.run();
			});
		}

		return AfterReadIni();
	}

	void ServerBase::Stop()
	{
		m_isRunning = false;
		m_ioContext.stop();
		m_workGuard.reset();
	}

	bool ServerBase::IsRunning() const
	{
		return m_isRunning;
	}

	asio::awaitable<void> ServerBase::Listen()
	{
		auto ReadLoop = [this](std::shared_ptr<BoostTcpSocket> pSocket) -> asio::awaitable<void>
			{
				while (m_isRunning)
				{
					if (!co_await pSocket->Read())
						break;
				}

				co_return;
			};

		auto WriteLoop = [this](std::shared_ptr<BoostTcpSocket> pSocket) -> asio::awaitable<void>
			{
				while (m_isRunning)
				{
					if (!co_await pSocket->Write())
						break;
				}

				co_return;
			};

		auto LogicLoop = [this](std::shared_ptr<IActor> pActor) -> asio::awaitable<void>
			{
				const auto updatePeriodMs = pActor->GetUpdatePeriodMs();
				while (m_isRunning)
				{
					using namespace std::chrono;
					using namespace std::chrono_literals;

					const auto startTime = steady_clock::now();
					{
						asio::co_spawn(m_ioContext,
							[&pActor]() -> asio::awaitable<void> { co_await pActor->Update(); },
							asio::detached);
					}
					const auto endTime = steady_clock::now();

					const auto elapsedTimeMs = duration_cast<milliseconds>(endTime - startTime).count();
					const auto leftTimeMs = updatePeriodMs - elapsedTimeMs;
					if (leftTimeMs > 0)
					{
						auto ex = co_await asio::this_coro::executor;
						asio::steady_timer timer(ex);
						timer.expires_after(std::chrono::microseconds(leftTimeMs));
						co_await timer.async_wait(asio::use_awaitable);
					}
				}

				co_return;
			};

		while (m_isRunning)
		{
			auto socket = co_await m_pAcceptor->async_accept(asio::use_awaitable);

			auto pSocket = std::make_shared<BoostTcpSocket>(std::move(socket));
			auto pActor = CreateActor(pSocket);
			NULL_CO_VOID_RETURN(pActor);

			pSocket->Initialize(pActor);

			if (!pActor->Initialize())
			{
				co_return;
			}

			pActor->OnAccepted();

			// Boost Asio TCP socket provides full duplex communication, so we can read and write at the same time.
			asio::co_spawn(pActor->GetStrand(), ReadLoop(pSocket),  asio::detached);
			asio::co_spawn(pActor->GetStrand(), WriteLoop(pSocket), asio::detached);

			asio::co_spawn(pActor->GetStrand(), LogicLoop(pActor),  asio::detached);
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