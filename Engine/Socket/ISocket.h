#pragma once

namespace GenericBoson
{
	class Message;

	namespace asio = boost::asio;

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

		virtual asio::awaitable<bool> Write() = 0;
		virtual asio::awaitable<bool> Read() = 0;

		virtual ESocketType GetType() = 0;
		virtual bool IsValid() const = 0;

		virtual void EnqueueMessage(
			const uint8_t* pBuffer,
			std::size_t bufferSize) = 0;

		virtual auto ConnectAsync(
			const std::string&             ip, 
			const std::string&             port,
			std::function<
				asio::awaitable<void>()>&& onConnected)
			-> asio::awaitable<bool> = 0;
	};
}