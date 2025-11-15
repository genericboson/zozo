#include "PCH.h"

#include "LobbyStub.h"
#include "LobbyStubManager.h"

namespace GenericBoson
{
	void LobbyStubManager::AddLobbyStub(std::shared_ptr<LobbyStub>&& pLobbyStub)
	{
		m_lobbyStubs[pLobbyStub->Id()] = pLobbyStub;
	}
}