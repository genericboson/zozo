#include "PCH.h"

#include <Engine/Socket/BoostTcpSocket.h>

#include "LobbyServer.h"

#include "Session/LobbyUser.h"
#include "Session/LobbyUserManager.h"

namespace GenericBoson
{
	LobbyServer::LobbyServer(int32_t port /*= 8002*/)
		: m_workGuard(m_ioContext.get_executor()), m_acceptor(
			m_ioContext, 
			boost::asio::ip::tcp::endpoint(
				boost::asio::ip::tcp::v4(), port))
	{
	}

	bool LobbyServer::Start()
	{
		INFO_LOG("LobbyServer started ( port - {} )",
			m_acceptor.local_endpoint().port());

		HandleAccept();

		m_ioContext.run();
		return true;
	}

	void LobbyServer::Stop()
	{
		m_ioContext.stop();
	}

	void LobbyServer::HandleAccept()
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
					auto pLobbyUser = std::make_shared<LobbyUser>(pSocket);
					INFO_LOG("Client accepted ( ClientId - {} )", pLobbyUser->Id());

					pSocket->Initialize(pLobbyUser);
					if (pLobbyUser->Initiailize())
					{
						LobbyUserManager::GetInstance()->AddLobbyUser(std::move(pLobbyUser));
					}
					else
					{
						WARN_LOG("lobby user initialize failed ( LobbyUserId - {} )", pLobbyUser->Id());
					}
				}

				HandleAccept();
			});
	}
}