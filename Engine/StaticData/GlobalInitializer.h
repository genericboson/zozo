#pragma once

#include <memory>
#include <utility>

#include "StaticDataManager.h"

namespace GenericBoson
{
	// 생성된 정적 데이터 .cpp 파일이 네임스페이스 스코프에 이 객체를 하나 둔다.
	// main() 진입 전 static 초기화 시점에 T의 프로토타입이 StaticDataManager에 등록된다.
	template< typename T >
	class GlobalInitializer
	{
	public:
		explicit GlobalInitializer(std::shared_ptr<T>&& pStaticData)
		{
			StaticDataManager::GetInstance()->InsertStaticData(
				T::CLASS_ID, std::move(pStaticData));
		}
	};
}
