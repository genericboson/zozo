#pragma once

#include <Engine/Singleton.h>

namespace GenericBoson
{
	class LobbyUser;

	class LobbyUserManager : public Singleton< LobbyUserManager >
	{
	public:
		void AddLobbyUser(std::shared_ptr< LobbyUser >&& pLobbyUser);

	private:
		std::unordered_map< int64_t, std::shared_ptr< LobbyUser > > m_lobbyUsers;
	};
}