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
		asio::awaitable<void> AddUnauthedUser(std::shared_ptr< LobbyUser >&& pLobbyUser);

		asio::awaitable<Zozo::ResultCode> AddLobbyUser(std::shared_ptr< LobbyUser >&& pLobbyUser);

	private:
		IdGenerator m_idGenerator;

		std::shared_mutex m_lobbyUsersMutex;
		std::unordered_map< int64_t, std::shared_ptr< LobbyUser > > m_unauthedLobbyUsers, m_lobbyUsers;
	};
}