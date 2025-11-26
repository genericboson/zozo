#pragma once

#include <Engine/Singleton.h>

#include "MessageSchema/Common/ServerInfo_generated.h"

namespace GenericBoson
{
	class LobbyStub;

	class LobbyStubManager : public Singleton< LobbyStubManager >
	{
	public:
		void AddRegisteredLobbyStub(std::shared_ptr< LobbyStub >&& pLobbyStub, int32_t serverId);
		void AddUnregisteredLobbyStub(std::shared_ptr< LobbyStub >&& pLobbyStub);

		auto GetRegisteredLobbyStub(int32_t serverId)
			-> std::shared_ptr<LobbyStub>;
		auto GetServerInfos(flatbuffers::FlatBufferBuilder& fbb)
			-> std::vector<flatbuffers::Offset<Zozo::ServerInfo>>;

	private:
		std::shared_mutex m_lock;
		int64_t m_unregisteredCount = 0;
		std::unordered_map< int64_t, std::shared_ptr< LobbyStub > > m_registeredStubs, m_unregisteredStubs;
	};
}