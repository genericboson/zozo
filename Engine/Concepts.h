#pragma once

#include "Types.h"
#include "Tx/CustomAttributes.h"

namespace GenericBoson
{
	template <typename T>
	concept IsString = std::convertible_to<T, std::string_view>;

	template <typename CALLABLE>
	concept MemTxPostCallbackLike = requires(CALLABLE f, MemTxPostCallback param) {
		f(param);
	};

	template <typename T>
	concept ReadableLike = std::derived_from<T, Readable>;

	template <typename T>
	concept WritableLike = std::derived_from<T, Writable>;
}