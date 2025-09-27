#pragma once

#include <boost/asio.hpp>

#include "ISocket.h"

namespace GenericBoson
{
	class ISocket;

	class BoostTcpSocket : public ISocket
	{
	public:
		BoostTcpSocket(
			boost::asio::ip::tcp::socket pSocket);

		void Start() override;
		void Write(const Message& msg) override;

		void Close();
		bool IsOpen() const;

	private:
		boost::asio::ip::tcp::socket m_socket;
	};
}