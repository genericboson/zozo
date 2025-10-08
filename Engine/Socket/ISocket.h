#pragma once

namespace GenericBoson
{
	class Message;

	enum class ESocketType
	{
		NONE = 0,
		BOOST_TCP = 1,
		BOOST_UDP = 2,
	};

	class ISocket
	{
	public:
		virtual ~ISocket() = default;

		virtual void Write(const Message& msg) = 0;
		virtual void ReadHeader() = 0;
		virtual void ReadBody() = 0;

		virtual ESocketType GetType() = 0;
		virtual bool IsValid() const = 0;
	};
}