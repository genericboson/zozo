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

	awaitable<void> ServerBase::Read(ip::tcp::socket&& socket)
	{
		auto pSocket = std::make_shared<BoostTcpSocket>(std::move(socket));
		auto pActor = CreateActor(pSocket);
		pSocket->Initialize(pActor);

		if (!pActor->Initialize())
		{
			co_return;
		}

		pActor->OnAccepted();

		while (m_isRunning)
		{
			co_await pSocket->Read();
		}
	}

	awaitable<void> ServerBase::Listen()
	{
		auto CallRead = [this](ip::tcp::socket&& socket) -> awaitable<void>
			{
				return Read(std::move(socket));
			};

		while (m_isRunning)
		{
			auto socket = co_await m_acceptor.async_accept(use_awaitable);
			co_spawn(m_acceptor.get_executor(), CallRead(std::move(socket)), detached);
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