#include "PCH.h"

#include "LobbyUser.h"
#include "LobbyUserManager.h"

namespace GenericBoson
{
	void LobbyUserManager::AddUnauthedUser(std::shared_ptr<LobbyUser>&& pLobbyUser)
	{
		std::unique_lock<std::shared_mutex> lock(m_lock);

		pLobbyUser->m_id = m_unauthedCount++;
		m_unauthedLobbyUsers[m_unauthedCount] = pLobbyUser;
	}

	asio::awaitable<Zozo::ResultCode> LobbyUserManager::AddLobbyUser(std::shared_ptr<LobbyUser>&& pLobbyUser, int64_t userId)
	{
		NULL_CO_RETURN(!userId, Zozo::ResultCode::ResultCode_InvalidId);

		std::unique_lock<std::shared_mutex> lock(m_lock);

		const auto oldId = pLobbyUser->Id();

		pLobbyUser->m_id = userId;

		if (m_lobbyUsers.contains(userId))
			co_return Zozo::ResultCode::ResultCode_AlreadyLoggedIn;

		m_lobbyUsers[userId] = pLobbyUser;
		m_unauthedLobbyUsers.erase(oldId);
		co_return Zozo::ResultCode::ResultCode_Success;
	}
}