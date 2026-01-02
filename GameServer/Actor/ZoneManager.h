#pragma once

#include <Engine/Singleton.h>

namespace GenericBoson
{
	class Zone;

	class ZoneManager : public GenericBoson::Singleton< ZoneManager >
	{
	public:
		bool EnterZone(const int64_t characterId, const int64_t x, const int64_t y);
	private:
		std::shared_mutex m_lock;
		std::unordered_map<int64_t, std::unordered_map<int64_t, std::shared_ptr<Zone>> m_zones;
	};
}