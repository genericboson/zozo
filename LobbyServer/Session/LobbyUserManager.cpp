#include "PCH.h"

#include "LobbyUser.h"
#include "LobbyUserManager.h"

namespace GenericBoson
{
	void LobbyUserManager::AddLobbyUser(std::shared_ptr<LobbyUser>&& pLobbyUser)
	{
		m_lobbyUsers[pLobbyUser->Id()] = pLobbyUser;
	}
}