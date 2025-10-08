#include "PCH.h"

#include <Engine/Socket/BoostTcpSocket.h>

#include "LobbyServer.h"

#include "Session/LobbyUser.h"
#include "Session/LobbyUserManager.h"

namespace GenericBoson
{
	LobbyServer::LobbyServer(int32_t port /*= 8002*/)
		: ServerBase(port)
	{
	}

	auto LobbyServer::CreateActor(const std::shared_ptr<ISocket>& pSocket)
		-> std::shared_ptr<IActor>
	{
		if (auto pLobbyUser = std::make_shared<LobbyUser>(pSocket);
			pLobbyUser->Initiailize())
		{
			LobbyUserManager::GetInstance()->AddLobbyUser(std::move(pLobbyUser));
			return pLobbyUser;
		}
		else
		{
			WARN_LOG("lobby user initialize failed ( LobbyUserId - {} )", pLobbyUser->Id());
		}

		return nullptr;
	}
}