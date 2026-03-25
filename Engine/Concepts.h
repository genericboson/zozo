#pragma once

#include "Types.h"
#include "Tx/CustomAttributes.h"

namespace GenericBoson
{
	template <typename T>
	concept IsString = std::convertible_to<T, std::string_view>;

	template <typename CALLABLE>
	concept CacheTxPostCallbackLike = requires(CALLABLE f, CacheTxPostCallback param) {
		f(param);
	};

	template <typename T, typename U>
	concept ReadableLike = std::derived_from<T, Readable<U>>;

	template <typename T, typename U>
	concept WritableLike = std::derived_from<T, Writable<U>>;
}