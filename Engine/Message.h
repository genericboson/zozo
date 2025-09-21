#pragma once

#include <cstdint>

namespace GenericBoson
{
	class Message
	{
	public:
		Message() = default;

		Message(const uint8_t* body, size_t bodySize);

	public:
	private:
		size_t m_bodySize;
	};
}