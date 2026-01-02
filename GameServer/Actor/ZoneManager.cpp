#include "PCH.h"
#include "ZoneManager.h"

namespace GenericBoson
{
	bool GenericBoson::ZoneManager::EnterZone(const int64_t characterId, const int64_t x, const int64_t y)
	{
		std::unique_lock lock{ m_lock };



		return true;
	}
}