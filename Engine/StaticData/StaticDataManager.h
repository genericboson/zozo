#pragma once

namespace GenericBoson
{
	class StaticDataBase
	{
	public:
		virtual ~StaticDataBase() = default;
		virtual void Insert(const boost::json::object& obj) = 0;
	};
	class StaticDataManager
	{
	public:
		static StaticDataManager* GetInstance();
		std::shared_ptr<StaticDataBase> CreateStaticData(int64_t classId);
	private:
		std::unordered_map<int64_t, std::shared_ptr<StaticDataBase>> m_staticDataMap;
	};
}