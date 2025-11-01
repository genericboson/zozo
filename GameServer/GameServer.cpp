#include "PCH.h"

#include <Engine/Socket/BoostTcpSocket.h>

#include "Actor/Character/Character.h"
#include "Actor/Character/CharacterManager.h"
#include "GameServer.h"

namespace GenericBoson
{
	GameServer::GameServer(int32_t port /*= 8001*/)
		: ServerBase(port)
	{
	}

	bool GameServer::Start()
	{
		// #todo - ini
		m_pClient = std::make_unique<InternalClient>(shared_from_this(), "127.0.0.1", "8002");

		const auto clientTask = [this]() -> asio::awaitable<void>
			{
				co_await m_pClient->Initialize();
			};

		asio::co_spawn(m_ioContext, clientTask, asio::detached);

		if (!ServerBase::Start())
		{
			ERROR_LOG("ServerBase::Start for GameServer failed");
			return false;
		}

		return true;
	}

	auto GameServer::CreateActor(const std::shared_ptr<ISocket>& pSocket) 
		-> std::shared_ptr<IActor>
	{
		return std::make_shared<Character>(pSocket);
	}
}