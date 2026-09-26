//============================================================
// 이 파일은 DataConverter가 item.xlsx 로부터 자동 생성했습니다.
// 직접 수정하지 마세요.
// 엑셀을 수정한 뒤 DataConverter를 다시 실행하면 갱신됩니다.
//============================================================

#include "PCH.h"

#include <Engine/StaticData/GlobalInitializer.h>
#include <Engine/StaticData/StaticDataParse.h>

#include "item.h"

namespace GenericBoson
{
	namespace
	{
		// main() 진입 전에 Item 프로토타입을 StaticDataManager에 등록한다.
		const GlobalInitializer<Item> g_itemInitializer{ std::make_shared<Item>() };
	}

	std::shared_ptr<IStaticData> Item::Create()
	{
		return std::make_shared<Item>();
	}

	void Item::Insert(const boost::json::object& obj)
	{
		StaticDataParse::Read(obj, "ID", m_ID);
		StaticDataParse::Read(obj, "Name", m_Name);
		StaticDataParse::Read(obj, "Effect", m_Effect);
		StaticDataParse::Read(obj, "Cost", m_Cost);

		// 파싱된 행을 자기 타입의 DataManager에 담는다.
		ItemDataManager::GetInstance()->Add(std::make_shared<Item>(*this));
	}

	bool ItemDataManager::Add(std::shared_ptr<Item>&& pData)
	{
		if (!pData)
		{
			return false;
		}

		const auto key = static_cast<int64_t>(pData->ID());
		if (m_data.contains(key))
		{
			WARN_LOG("Duplicated Item key in static data.");
			return false;
		}

		m_data.emplace(key, std::move(pData));
		return true;
	}

	std::shared_ptr<const Item> ItemDataManager::Get(int64_t key) const
	{
		const auto found = m_data.find(key);
		if (found == m_data.end())
		{
			return nullptr;
		}

		return found->second;
	}
}
