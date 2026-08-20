#pragma once

#include <boost/json.hpp>

#include <Engine/Singleton.h>

namespace GenericBoson
{
	class StaticDataManager : public Singleton<StaticDataManager>
	{
	public:
		bool InsertStaticData(int64_t classId, std::shared_ptr<IStaticData>&& pNewStaticData);
	private:
		std::unordered_map<int64_t, std::shared_ptr<IStaticData>> m_data;
	};
}