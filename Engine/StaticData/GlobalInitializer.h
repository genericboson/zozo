#pragma once

#include "StaticDataManager.h"

namespace GenericBoson
{
	template< typename T >
	class GlobalInitializer
	{
	public:
		GlobalInitializer(std::shared_ptr<T>&& t)
		{
			StaticDataManager::GetInstance()->InsertStaticData(1, std::move(t));
		}
	};
}