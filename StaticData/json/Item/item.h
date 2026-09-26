#pragma once

//============================================================
// 이 파일은 DataConverter가 item.xlsx 로부터 자동 생성했습니다.
// 직접 수정하지 마세요.
// 엑셀을 수정한 뒤 DataConverter를 다시 실행하면 갱신됩니다.
//============================================================

#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>

#include <boost/json.hpp>

#include <Engine/Singleton.h>
#include <Engine/StaticData/IStaticData.h>

namespace GenericBoson
{
	class Item : public IStaticData
	{
	public:
		// FnvHash64("item")
		static constexpr int64_t CLASS_ID = 2900776405502981158LL;

		void Insert(const boost::json::object& obj) override;
		std::shared_ptr<IStaticData> Create() override;

		int32_t            ID() const { return m_ID; }
		const std::string& Name() const { return m_Name; }
		const std::string& Effect() const { return m_Effect; }
		int32_t            Cost() const { return m_Cost; }

	private:
		int32_t     m_ID{};
		std::string m_Name{};
		std::string m_Effect{};
		int32_t     m_Cost{};
	};

	// Item 행들을 ID 기준으로 보관한다.
	class ItemDataManager : public Singleton<ItemDataManager>
	{
	public:
		// 키가 이미 있으면 false. Item::Insert()가 호출한다.
		bool Add(std::shared_ptr<Item>&& pData);

		// 없으면 nullptr.
		std::shared_ptr<const Item> Get(int64_t key) const;

		const std::unordered_map<int64_t, std::shared_ptr<Item>>& GetAll() const { return m_data; }
		std::size_t Size() const { return m_data.size(); }

	private:
		std::unordered_map<int64_t, std::shared_ptr<Item>> m_data;
	};
}
