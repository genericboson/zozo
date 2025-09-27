#include "PCH.h"

#include <boost/asio/ip/tcp.hpp>

#include "BoostTcpSocket.h"

namespace GenericBoson
{
	BoostTcpSocket::BoostTcpSocket(
		boost::asio::ip::tcp::socket pSocket)
		: m_socket(std::move(pSocket))
	{
	}

	void BoostTcpSocket::Close()
	{
		if (!IsOpen())
			return;

		boost::system::error_code ec;
		m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
		m_socket.close(ec);
	}

	bool BoostTcpSocket::IsOpen() const
	{
		return m_socket.is_open();
	}

	void BoostTcpSocket::Start()
	{
	}

	void BoostTcpSocket::Write(const Message& msg)
	{
	}
}
