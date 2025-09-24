#include "PCH.h"

#include <boost/asio/ip/tcp.hpp>

#include "BoostTcpSocket.h"
#include "ISocket.h"

name GenericBoson
{
	BoostTcpSocket::BoostTcpSocket(
		std::shared_ptr< boost::asio::ip::tcp::socket > pSocket)
		: m_pSocket(pSocket)
	{
	}

	void BoostTcpSocket::Close()
	{
		if (!m_pSocket)
			return;
			
		if (m_pSocket->is_open())
			return;

		boost::system::error_code ec;
		m_pSocket->shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
		m_pSocket->close(ec);
	}

	bool BoostTcpSocket::IsOpen() const
	{
		return m_pSocket && m_pSocket->is_open();
	}

	void BoostTcpSocket::Start()
	{
	}

	void BoostTcpSocket::Write(const Message& msg)
	{
	}
}
