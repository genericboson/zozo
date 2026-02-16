#pragma once

#include "Types.h"

namespace GenericBoson
{
	template <typename T>
	concept IsString = std::convertible_to<T, std::string_view>;

	template <typename CALLABLE>
	concept CacheTxPostCallbackLike = requires(CALLABLE f, CacheTxPostCallback param) {
		f(param);
	};
}