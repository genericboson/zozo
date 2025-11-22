#pragma once

#include <Engine/Singleton.h>

#include "MessageSchema/Common/ServerInfo_generated.h"

namespace GenericBoson
{
	class LobbyStub;

	class LobbyStubManager : public Singleton< LobbyStubManager >
	{
	public:
		void AddLobbyStub(std::shared_ptr< LobbyStub >&& pLobbyStub);
		auto GetServerInfos(flatbuffers::FlatBufferBuilder& fbb)
			-> std::vector<flatbuffers::Offset<Zozo::ServerInfo>>;

	private:
		std::shared_mutex m_lock;

	private:
		std::unordered_map< int64_t, std::shared_ptr< LobbyStub > > m_lobbyStubs;
	};
}