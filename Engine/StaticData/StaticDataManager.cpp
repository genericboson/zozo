#include "PCH.h"

#include "IProtoType.h"
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
}