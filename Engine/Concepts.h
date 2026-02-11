#pragma once

namespace GenericBoson
{
	template <typename T>
	concept IsString = std::convertible_to<T, std::string_view>;
}