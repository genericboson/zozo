#include "PCH.h"

#include "StaticDataManager.h"

namespace GenericBoson
{
	std::shared_ptr<StaticDataBase> StaticDataManager::CreateStaticData(int64_t classId)
	{
		auto iter = m_staticDataMap.find(classId);
		if (iter != m_staticDataMap.end())
		{
			return iter->second;
		}
		std::shared_ptr<StaticDataBase> staticData;
		switch (classId)
		{
		case 1: // Zone
			staticData = std::make_shared<ZoneStaticData>();
			break;
		case 2: // Item
			staticData = std::make_shared<ItemStaticData>();
			break;
		default:
			WARN_LOG("Unknown CLASS_ID {} in static data file", classId);
			return nullptr;
		}
		m_staticDataMap[classId] = staticData;
		return staticData;
	}

	StaticDataManager* StaticDataManager::GetInstance()
	{
		static StaticDataManager instance;
		return &instance;
	}
}