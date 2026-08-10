#pragma once

#include <cstdint>
#include <string>

namespace GenericBoson
{

	class ItemDataManager
	{
	}

	class Item : IStaticData
	{
	public:
		int32_t ID();
		std::string Name();
		std::string Effect();
		int32_t Cost();
	};
}
