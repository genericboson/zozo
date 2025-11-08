#include "PCH.h"

#include <flatbuffers/flatbuffers.h>
#include <Engine/Socket/BoostTcpSocket.h>

#include "Actor/Character/Character.h"
#include "Actor/Character/CharacterManager.h"
#include "GameServer.h"

#include <MessageSchema/Internal/LobbyGame_generated.h>

namespace GenericBoson
{
	GameServer::GameServer(int32_t port /*= 8001*/)
		: ServerBase(port)
	{
	}

	bool GameServer::Start()
	{
		if (!ServerBase::Start())
		{
			ERROR_LOG("ServerBase::Start for GameServer failed");
			return false;
		}

		// #todo - ini
		m_pClient = std::make_unique<InternalClient>(shared_from_this(), "127.0.0.1", "8002");
		m_pClient->SetOnConnected([this]() {
			flatbuffers::FlatBufferBuilder fbb;

			auto nameStr = fbb.CreateString("");
			auto req = Zozo::CreateRegisterReq(fbb, nameStr);
			auto msg = Zozo::CreateLobbyGameMessage(fbb, 
				Zozo::LobbyGamePayload::LobbyGamePayload_RegisterReq, 
				req.Union());

			fbb.Finish(msg);
			
			m_pClient->EnqueueMessage(fbb.GetBufferPointer(), fbb.GetSize());
		});

		const auto clientTask = [this]() -> asio::awaitable<void>
			{
				co_await m_pClient->KeepSending(m_pLobbyProxy);
			};

		asio::co_spawn(m_ioContext, clientTask, asio::detached);

		INFO_LOG("GameServer started ( port - {} )", m_listeningPort);
		return true;
	}

	auto GameServer::CreateActor(const std::shared_ptr<ISocket>& pSocket) 
		-> std::shared_ptr<IActor>
	{
		return std::make_shared<Character>(shared_from_this(), pSocket);
	}

	auto GameServer::CreateGameServer(int32_t port /*= 8001*/) -> std::shared_ptr<GameServer>
	{
		return std::make_shared<GameServer>(port);
	}
}