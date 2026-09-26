#pragma once

#include <cstdint>
#include <string_view>

namespace GenericBoson
{
	// 정적 데이터 파일명(확장자 없는 소문자)으로부터 CLASS_ID를 만든다.
	// DataConverter(C#)의 StaticDataId.FnvHash64와 반드시 동일한 알고리즘이어야 한다.
	constexpr uint64_t FnvHash64(std::string_view name) noexcept
	{
		uint64_t hash = 0xcbf29ce484222325ULL;
		for (const unsigned char c : name)
		{
			hash ^= c;
			hash *= 0x100000001b3ULL;
		}
		return hash;
	}

	constexpr int64_t MakeStaticDataId(std::string_view name) noexcept
	{
		return static_cast<int64_t>(FnvHash64(name));
	}

	// 사용 예 : constexpr int64_t id = "item"_static_data_id;
	constexpr int64_t operator""_static_data_id(const char* pName, std::size_t length) noexcept
	{
		return MakeStaticDataId(std::string_view{ pName, length });
	}
}
