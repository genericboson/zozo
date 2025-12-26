#include "PCH.h"

#include "LobbyUser.h"
#include "LobbyUserManager.h"

namespace GenericBoson
{
	void LobbyUserManager::AddLobbyUser(std::shared_ptr<LobbyUser>&& pLobbyUser)
	{
		NULL_RETURN(!pLobbyUser->m_id);

		//pLobbyUser->m_id = 

		m_lobbyUsers[pLobbyUser->Id()] = pLobbyUser;
	}
}