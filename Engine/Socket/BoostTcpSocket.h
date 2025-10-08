#pragma once

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/use_awaitable.hpp>

#include "Engine/IActor.h"
#include "ISocket.h"
#include "Message.h"

namespace GenericBoson
{
	class ISocket;

	using namespace boost::asio;

	class BoostTcpSocket : public ISocket
	{
	public:
		BoostTcpSocket(ip::tcp::socket pSocket);

		void Initialize(const std::shared_ptr<IActor>& pOwner);

		awaitable<void> Write(const Message& msg) override;
		awaitable<void> Read() override;

		ESocketType GetType() override;
		bool IsValid() const override;

		void Close();
		bool IsOpen() const;

	private:
		ip::tcp::socket              m_socket;
		Message				         m_readMsg;

		std::weak_ptr<IActor>        m_wpOwner;
	};
}