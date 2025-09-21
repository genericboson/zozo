#include "PCH.h"

#include "Message.h"

namespace GenericBoson
{
	Message::Message(const uint8_t* body, size_t bodySize)
		: m_bodySize ( bodySize )
	{
		assert(bodySize <= maxBodySize);
	}
}