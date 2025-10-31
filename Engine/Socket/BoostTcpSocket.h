#pragma once

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/asio/experimental/awaitable_operators.hpp>
#include <boost/asio/experimental/concurrent_channel.hpp>

#include "Engine/IActor.h"
#include "ISocket.h"
#include "Message.h"

namespace GenericBoson
{
	class ISocket;

	namespace asio = boost::asio;
	using namespace boost::asio::experimental::awaitable_operators;

	class BoostTcpSocket : public ISocket
	{
	public:
		BoostTcpSocket(asio::ip::tcp::socket pSocket);

		void Initialize(const std::shared_ptr<IActor>& pOwner);

		asio::awaitable<bool> Write() override;
		asio::awaitable<bool> Read() override;

		ESocketType GetType() override;
		bool IsValid() const override;

		void Close();
		bool IsOpen() const;
		bool IsSucceeded(boost::system::error_code errorCode) const;

		void EnqueueMessage(
			const uint8_t* pBuffer, 
			std::size_t bufferSize) override;

		auto ConnectAsync(
			const std::string&             ip,
			const std::string&             port,
			std::function<
				asio::awaitable<void>()>&& onConnected)
			-> asio::awaitable<bool>;

	private:
		enum { WRITE_CHANNEL_SIZE = 4096 };

	private:
		asio::ip::tcp::socket        m_socket;
		Message				         m_readMsg;
		asio::experimental::concurrent_channel<
			void(boost::system::error_code, Message)>
			                         m_writeChannel;

		std::weak_ptr<IActor>        m_wpOwner;
	};
}