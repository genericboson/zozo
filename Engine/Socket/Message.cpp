#include "PCH.h"

#include "Message.h"

namespace GenericBoson
{
	Message::Message(const uint8_t* body, size_t bodySize)
		: m_bodySize ( bodySize )
	{
		assert(bodySize <= MAX_BODY_SIZE);
	}

	const uint8_t* Message::Data() const
	{
		return m_pData;
	}

	uint8_t* Message::Data()
	{
		return m_pData;
	}

	std::size_t Message::Length() const
	{
		return HEADER_SIZE + m_bodySize;
	}

	const uint8_t* Message::Body() const
	{
		return m_pData + HEADER_SIZE;
	}

	uint8_t* Message::Body()
	{
		return m_pData + HEADER_SIZE;
	}

	std::size_t Message::BodySize() const
	{
		return m_bodySize;
	}

	void Message::BodySize(std::size_t newSize)
	{
		assert(newSize <= MAX_BODY_SIZE);
		m_bodySize = newSize;
	}

	bool Message::DecodeHeader()
	{
		auto intArray = (int32_t*)(m_pData);
		if (intArray[0] <= MAX_BODY_SIZE)
		{
			m_bodySize = intArray[0];
			return true;
		}

		return false;
	}

	void Message::EncodeHeader()
	{
		auto intArray = (int32_t*)(m_pData);
		intArray[0] = m_bodySize;
	}
}