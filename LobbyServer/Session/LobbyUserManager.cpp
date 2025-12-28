#include "PCH.h"

#include "LobbyUser.h"
#include "LobbyUserManager.h"

namespace GenericBoson
{
	asio::awaitable<void> LobbyUserManager::AddUnauthedUser(std::shared_ptr<LobbyUser>&& pLobbyUser)
	{
		return asio::awaitable<void>();
	}

	asio::awaitable<Zozo::ResultCode> LobbyUserManager::AddLobbyUser(std::shared_ptr<LobbyUser>&& pLobbyUser)
	{
		NULL_CO_RETURN(!pLobbyUser->m_id, Zozo::ResultCode::ResultCode_InvalidId);

		if (m_lobbyUsers.contains(pLobbyUser->Id()))
			co_return Zozo::ResultCode::ResultCode_AlreadyLoggedIn;

		m_lobbyUsers[pLobbyUser->Id()] = pLobbyUser;
		co_return Zozo::ResultCode::ResultCode_Success;
	}
}