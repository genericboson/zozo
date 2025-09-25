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
		char header[HEADER_SIZE + 1] = { 0, };
		strncat_s(header, (char*)m_pData, HEADER_SIZE);
		m_bodySize = std::atoi(header);
		if (m_bodySize <= MAX_BODY_SIZE)
			return true;

		m_bodySize = 0;
		return false;
	}

	void Message::EncodeHeader()
	{
		char header[HEADER_SIZE + 1] = { 0, };
		sprintf_s(header, "%4d", static_cast<int32_t>(m_bodySize));
		memcpy_s(m_pData, HEADER_SIZE + MAX_BODY_SIZE, header, HEADER_SIZE);
	}
}