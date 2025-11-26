#include "PCH.h"

#include <flatbuffers/flatbuffers.h>
#include <ranges>

#include "LobbyStub.h"
#include "LobbyStubManager.h"

namespace GenericBoson
{
	void LobbyStubManager::AddUnregisteredLobbyStub(std::shared_ptr<LobbyStub>&& pLobbyStub)
	{
		std::unique_lock<std::shared_mutex> lock(m_lock);

		pLobbyStub->m_id = m_unregisteredCount++;
		m_unregisteredStubs[m_unregisteredCount] = pLobbyStub;
	}

	void LobbyStubManager::AddRegisteredLobbyStub(std::shared_ptr<LobbyStub>&& pLobbyStub, int32_t serverId)
	{
		std::unique_lock<std::shared_mutex> lock(m_lock);

		const auto oldId = pLobbyStub->Id();

		pLobbyStub->m_id = serverId;
		m_registeredStubs[pLobbyStub->Id()] = pLobbyStub;

		m_unregisteredStubs.erase(oldId);
	}

	auto LobbyStubManager::GetRegisteredLobbyStub(int32_t serverId)
		-> std::shared_ptr<LobbyStub>
	{
		std::shared_lock<std::shared_mutex> lock(m_lock);

		if (const auto found = m_registeredStubs.find(serverId);
			found != m_registeredStubs.end())
			return found->second;

		return nullptr;
	}

	auto LobbyStubManager::GetServerInfos(flatbuffers::FlatBufferBuilder& fbb)
		->  std::vector<flatbuffers::Offset<Zozo::ServerInfo>>
	{
		std::vector<flatbuffers::Offset<Zozo::ServerInfo>> infos;

		std::shared_lock<std::shared_mutex> lock(m_lock);

		infos.reserve(m_registeredStubs.size());

		for (const auto& pLobbyStub : m_registeredStubs | std::views::values )
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