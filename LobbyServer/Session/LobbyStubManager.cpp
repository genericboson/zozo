#include "PCH.h"

#include <flatbuffers/flatbuffers.h>
#include <ranges>

#include "LobbyStub.h"
#include "LobbyStubManager.h"
#include "MessageSchema/Common/ServerInfo_generated.h"

namespace GenericBoson
{
	void LobbyStubManager::AddLobbyStub(std::shared_ptr<LobbyStub>&& pLobbyStub)
	{
		std::unique_lock<std::shared_mutex> lock(m_lock);

		m_lobbyStubs[pLobbyStub->Id()] = pLobbyStub;
	}

	auto LobbyStubManager::GetServerInfos(flatbuffers::FlatBufferBuilder& fbb)
		->  std::vector<flatbuffers::Offset<Zozo::ServerInfo>>
	{
		std::vector<flatbuffers::Offset<Zozo::ServerInfo>> infos;

		std::shared_lock<std::shared_mutex> lock(m_lock);

		infos.reserve(m_lobbyStubs.size());

		for (const auto& pLobbyStub : m_lobbyStubs | std::views::values )
		{
			auto nameStrOffset = fbb.CreateString(pLobbyStub->m_name);
			auto ipStrOffset   = fbb.CreateString(pLobbyStub->m_ip);
			auto portStrOffset = fbb.CreateString(pLobbyStub->m_port);

			auto serverInfo = Zozo::CreateServerInfo(fbb, 
				pLobbyStub->m_id, nameStrOffset, ipStrOffset, portStrOffset, 
				pLobbyStub->m_currentCCU, pLobbyStub->m_maxCCU);

			infos.emplace_back(std::move(serverInfo));
		}

		return infos;
	}
} 