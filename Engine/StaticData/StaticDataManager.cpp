#include "PCH.h"

#include "IStaticData.h"
#include "StaticDataManager.h"

namespace GenericBoson
{
	bool StaticDataManager::InsertStaticData(int64_t classId, std::shared_ptr<IStaticData>&& pNewStaticData)
	{
		auto iter = m_data.find(classId);
		if (iter != m_data.end())
		{
			return false;
		}
		m_data[classId] = std::move(pNewStaticData);
		return true;
	}

	std::shared_ptr<IStaticData> StaticDataManager::CreateStaticData(int64_t classId) const
	{
		const auto found = m_data.find(classId);
		if (found == m_data.end())
		{
			return nullptr;
		}

		return found->second->Create();
	}
}
