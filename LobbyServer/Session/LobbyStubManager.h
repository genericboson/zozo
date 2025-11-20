#pragma once

#include <Engine/Singleton.h>

namespace GenericBoson
{
	class LobbyStub;

	class LobbyStubManager : public Singleton< LobbyStubManager >
	{
	public:
		void AddLobbyStub(std::shared_ptr< LobbyStub >&& pLobbyStub);
		std::vector<int64_t> GetServerIds();

	private:
		std::shared_mutex m_lock;

	private:
		std::unordered_map< int64_t, std::shared_ptr< LobbyStub > > m_lobbyStubs;
	};
}