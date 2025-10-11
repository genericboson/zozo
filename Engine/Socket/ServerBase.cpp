#include "PCH.h"

#include "ServerBase.h"

#include "BoostTcpSocket.h"

namespace GenericBoson
{
	ServerBase::ServerBase(int32_t port)
		: m_workGuard(m_acceptIoContext.get_executor()), m_acceptor(
			m_acceptIoContext,
			boost::asio::ip::tcp::endpoint(
				boost::asio::ip::tcp::v4(), port))
	{
	}

	bool ServerBase::Start()
	{
		INFO_LOG("LobbyServer started ( port - {} )",
			m_acceptor.local_endpoint().port());

		Accept();

		m_acceptIoContext.run();

		return true;
	}

	void ServerBase::Stop()
	{
		m_isRunning = false;
		m_acceptIoContext.stop();
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
							co_await pSocket->Write();
						}
					};

				co_spawn(co_await this_coro::executor, WriteLoop(pSocket), detached);
				while (m_isRunning)
				{
					co_await pSocket->Read();
				}
			};

		while (m_isRunning)
		{
			auto socket = co_await m_acceptor.async_accept(use_awaitable);

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

		co_spawn(m_acceptIoContext, CallListen, detached);
	}
}