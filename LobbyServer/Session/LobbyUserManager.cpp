#include "PCH.h"

#include "LobbyUser.h"
#include "LobbyUserManager.h"

namespace GenericBoson
{
	void LobbyUserManager::AddUnauthedUser(std::shared_ptr<LobbyUser>&& pLobbyUser)
	{
		const auto checkAlreadyOccupied = [this]() {
			if (m_unauthedLobbyUsers.contains(m_unauthedCount) &&
				m_unauthedLobbyUsers[m_unauthedCount] != nullptr)
			{
				ERROR_LOG("Already occupied unauthed lobby users map index : {}", m_unauthedCount);
				return false;
			}
			return true;
		};

		{
			std::shared_lock<std::shared_mutex> lock(m_lock);

			if (!checkAlreadyOccupied())
				return;
		}

		std::unique_lock<std::shared_mutex> lock(m_lock);

		if (!checkAlreadyOccupied())
			return;

		pLobbyUser->m_temporaryId = m_unauthedCount;
		m_unauthedLobbyUsers[m_unauthedCount] = pLobbyUser;

		if (m_unauthedCount == std::numeric_limits<decltype(m_unauthedCount)>::max())
		{
			m_unauthedCount = 1;
			return;
		}
		m_unauthedCount++;
	}

	asio::awaitable<Zozo::ResultCode> LobbyUserManager::AddLobbyUser(std::shared_ptr<LobbyUser>&& pLobbyUser, int64_t userId)
	{
		std::unique_lock<std::shared_mutex> lock(m_lock);

		pLobbyUser->m_id = userId;

		if (m_lobbyUsers.contains(userId))
			co_return Zozo::ResultCode::ResultCode_AlreadyLoggedIn;

		m_lobbyUsers[userId] = pLobbyUser;
		m_unauthedLobbyUsers.erase(pLobbyUser->m_temporaryId);
		co_return Zozo::ResultCode::ResultCode_Success;
	}

	void LobbyUserManager::RemoveLobbyUser(std::shared_ptr<LobbyUser>&& pLobbyUser)
	{
		std::unique_lock<std::shared_mutex> lock(m_lock);

		m_lobbyUsers.erase(pLobbyUser->m_id);
		m_unauthedLobbyUsers.erase(pLobbyUser->m_temporaryId);
	}
}