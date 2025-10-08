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

		HandleAccept();

		m_ioContext.run();
		return true;
	}

	void ServerBase::Stop()
	{
		m_ioContext.stop();
	}

	void ServerBase::HandleAccept()
	{
		m_acceptor.async_accept(
			[this](const boost::system::error_code& error,
				boost::asio::ip::tcp::socket socket)
			{
				if (error)
				{
					WARN_LOG("error ( error value - {} )", error.value());
				}
				else
				{
					auto pSocket = std::make_shared<BoostTcpSocket>(std::move(socket));
					auto pActor = CreateActor(pSocket);
					pSocket->Initialize(pActor);

					pActor->OnAccepted();
				}

				HandleAccept();
			});
	}
}