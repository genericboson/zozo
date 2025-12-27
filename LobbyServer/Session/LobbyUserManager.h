#pragma once

#include <Engine/Numeric/IdGenerator.h>
#include <Engine/Singleton.h>

namespace Zozo
{
	enum class ResultCode : uint32_t;
}

namespace GenericBoson
{
	namespace asio = boost::asio;

	class LobbyUser;

	class LobbyUserManager : public Singleton< LobbyUserManager >
	{
	public:
		asio::awaitable<Zozo::ResultCode> AddLobbyUser(std::shared_ptr< LobbyUser >&& pLobbyUser);

	private:
		IdGenerator m_idGenerator;

		std::unordered_map< int64_t, std::shared_ptr< LobbyUser > > m_lobbyUsers;
	};
}