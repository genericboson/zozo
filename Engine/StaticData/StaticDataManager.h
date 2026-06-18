#pragma once

#include <boost/json.hpp>

#include <Engine/Singleton.h>

namespace GenericBoson
{
	class StaticDataBase : public Singleton<StaticDataBase>
	{
	public:
		virtual ~StaticDataBase() = default;
		virtual void Insert(const boost::json::object& obj) = 0;
	};
	class StaticDataManager
	{
	public:
		std::shared_ptr<IStaticData> CreateStaticData(int64_t classId);
		bool InsertStaticData(const std::shared_ptr<IStaticData>& pNewStaticData);
	private:
		std::unordered_map<int64_t, std::shared_ptr<IStaticData>> m_protoTypes;
	};
}