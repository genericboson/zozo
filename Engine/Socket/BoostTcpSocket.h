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

	using namespace boost::asio;
	using namespace boost::asio::experimental::awaitable_operators;

	class BoostTcpSocket : public ISocket
	{
	public:
		BoostTcpSocket(ip::tcp::socket pSocket);

		void Initialize(const std::shared_ptr<IActor>& pOwner);

		awaitable<void> Write() override;
		awaitable<void> Read() override;

		ESocketType GetType() override;
		bool IsValid() const override;

		void Close();
		bool IsOpen() const;
		bool IsSucceeded(boost::system::error_code errorCode) const;

		void EnqueueMessage(
			const uint8_t* pBuffer, 
			std::size_t bufferSize) override;

	private:
		enum { WRITE_CHANNEL_SIZE = 4096 };

	private:
		ip::tcp::socket              m_socket;
		Message				         m_readMsg;
		experimental::concurrent_channel<
			void(boost::system::error_code, Message)>
			                         m_writeChannel;

		std::weak_ptr<IActor>        m_wpOwner;
	};
}