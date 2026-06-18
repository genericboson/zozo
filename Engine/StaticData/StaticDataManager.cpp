#include "PCH.h"

#include "IProtoType.h"
#include "StaticDataManager.h"

namespace GenericBoson
{
	std::shared_ptr<IStaticData> StaticDataManager::CreateStaticData(int64_t classId)
	{
		auto iter = m_protoTypes.find(classId);
		if (iter != m_protoTypes.end())
		{
			NULL_RETURN(iter->second, nullptr);
			return iter->second->Clone();
		}
		return nullptr;
	}

	bool StaticDataManager::InsertStaticData(const std::shared_ptr<IStaticData>& pNewStaticData)
	{
		return false;
	}
}