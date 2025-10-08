#include "PCH.h"

#include "ServerBase.h"

#include "BoostTcpSocket.h"

namespace GenericBoson
{
	ServerBase::ServerBase(int32_t port)
		: m_workGuard(m_ioContext.get_executor()), m_acceptor(
			m_ioContext,
			boost::asio::ip::tcp::endpoint(
				boost::asio::ip::tcp::v4(), port))
	{
	}

	bool ServerBase::Start()
	{
		INFO_LOG("LobbyServer started ( port - {} )",
			m_acceptor.local_endpoint().port());

		Accept();

		m_ioContext.run();

		return true;
	}

	void ServerBase::Stop()
	{
		m_isRunning = false;
		m_ioContext.stop();
	}

	awaitable<void> ServerBase::Listen()
	{
		auto ReadLoop = [this](std::shared_ptr<BoostTcpSocket> pSocket) -> awaitable<void>
			{
				while (m_isRunning)
				{
					co_await pSocket->Read();
				}
			};

		auto WriteLoop = [this](std::shared_ptr<BoostTcpSocket> pSocket) -> awaitable<void>
			{
				while (m_isRunning)
				{
					co_await pSocket->Write();
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

			co_spawn(socket.get_executor(), ReadLoop(pSocket), detached);
			co_spawn(socket.get_executor(), WriteLoop(pSocket), detached);
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