#include "PCH.h"

#include "LobbyStub.h"
#include "LobbyStubManager.h"

namespace GenericBoson
{
	void LobbyStubManager::AddLobbyStub(std::shared_ptr<LobbyStub>&& pLobbyStub)
	{
		std::unique_lock<std::shared_mutex> lock(m_lock);

		m_lobbyStubs[pLobbyStub->Id()] = pLobbyStub;
	}

	std::vector<int64_t> LobbyStubManager::GetServerIds()
	{
		std::vector<int64_t> ids;

		ids.reserve(m_lobbyStubs.size());

		ids.assign(m_lobbyStubs.begin(), m_lobbyStubs.end());

		return ids;
	}
}