#pragma once

#include <Engine/Numeric/IdGenerator.h>
#include <Engine/Singleton.h>

#include "MessageSchema/Common/Constant_generated.h"

namespace GenericBoson
{
	namespace asio = boost::asio;

	class LobbyUser;

	class LobbyUserManager : public Singleton< LobbyUserManager >
	{
	public:
		void AddUnauthedUser(std::shared_ptr< LobbyUser >&& pLobbyUser);

		asio::awaitable<Zozo::ResultCode> AddLobbyUser(std::shared_ptr<LobbyUser>&& pLobbyUser, int64_t userId);

	private:
		IdGenerator m_idGenerator;

		std::shared_mutex m_lock;
		int64_t m_unauthedCount = 0;
		std::unordered_map< int64_t, std::shared_ptr< LobbyUser > > m_unauthedLobbyUsers, m_lobbyUsers;
	};
}