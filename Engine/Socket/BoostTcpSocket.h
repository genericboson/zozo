#pragma once

#include <boost/asio.hpp>

#include "Engine/IActor.h"
#include "ISocket.h"
#include "Message.h"

namespace GenericBoson
{
	class ISocket;

	class BoostTcpSocket : public ISocket
	{
	public:
		BoostTcpSocket(
			boost::asio::ip::tcp::socket pSocket);

		void Initialize(const std::shared_ptr<IActor>& pOwner);

		void Write(const Message& msg) override;
		void ReadHeader() override;
		void ReadBody() override;

		ESocketType GetType() override;
		bool IsValid() const override;

		void Close();
		bool IsOpen() const;

	private:
		boost::asio::ip::tcp::socket m_socket;
		Message				         m_readMsg;

		std::weak_ptr<IActor>        m_wpOwner;
	};
}