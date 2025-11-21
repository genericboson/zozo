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
		std::vector<flatbuffers::Offset<Zozo::ServerInfo>> strs;

		std::shared_lock<std::shared_mutex> lock(m_lock);

		strs.reserve(m_lobbyStubs.size());

		for (const auto& pLobbyStub : m_lobbyStubs | std::views::values )
		{
			auto strOffset = fbb.CreateString(std::format(
				"[{}] {}", pLobbyStub->m_id, pLobbyStub->m_name));

			strs.emplace_back(std::move(strOffset));
		}

		return strs;
	}
} 