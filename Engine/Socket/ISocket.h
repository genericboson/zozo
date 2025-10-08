#pragma once

namespace GenericBoson
{
	class Message;

	using namespace boost::asio;

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

		virtual awaitable<void> Write(const Message& msg) = 0;
		virtual awaitable<void> Read() = 0;

		virtual ESocketType GetType() = 0;
		virtual bool IsValid() const = 0;
	};
}