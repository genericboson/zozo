#include "PCH.h"

#include "Zone.h"
#include "ZoneManager.h"

namespace GenericBoson
{
	asio::awaitable<bool> ZoneManager::Initialize()
	{
		std::unique_lock lock{ m_lock };

		// #todo : temporary test code. Load zone data from file or database
		m_zones[0][0] = std::make_shared<Zone>();
		co_return true;
	}

	bool ZoneManager::EnterZone(const std::shared_ptr<Character>& pCharacter, const int64_t x, const int64_t y)
	{
		std::shared_lock lock{ m_lock };

		// #todo : temporary test code. Find zone by x, y
		m_zones[0][0]->Enter(pCharacter);

		return true;
}
	}