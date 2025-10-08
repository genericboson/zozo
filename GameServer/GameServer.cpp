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

	auto GameServer::CreateActor(const std::shared_ptr<ISocket>& pSocket) 
		-> std::shared_ptr<IActor>
	{
		if (auto pCharacter = std::make_shared<Character>(pSocket); 
			pCharacter->Initiailize())
		{
			CharacterManager::GetInstance()->AddCharacter(std::move(pCharacter));
			return pCharacter;
		}
		else
		{
			WARN_LOG("character initialize failed ( CharacterId - {} )", pCharacter->Id());
		}

		return nullptr;
	}
}