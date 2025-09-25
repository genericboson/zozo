#pragma once

namespace GenericBoson
{
	class Message
	{
	public:
		Message() = default;

		Message(const uint8_t* body, size_t bodySize);

		const uint8_t* Data() const;

		uint8_t* Data();

		std::size_t Length() const;

		const uint8_t* Body() const;

		uint8_t* Body();

		std::size_t BodySize() const;

		void BodySize(std::size_t newSize);

		bool DecodeHeader();

		void EncodeHeader();

	public:
		enum {HEADER_SIZE   = 4  };
		enum {MAX_BODY_SIZE = 512};
	private:
		uint8_t m_pData[HEADER_SIZE + MAX_BODY_SIZE] = { 0, };
		std::size_t m_bodySize;
	};
}