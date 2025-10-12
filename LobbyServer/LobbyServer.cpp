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
		return std::make_shared<LobbyUser>(*this, pSocket);
	}
}