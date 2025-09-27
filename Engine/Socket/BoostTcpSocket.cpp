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

	void BoostTcpSocket::Initialize(const std::shared_ptr<IActor>& pOwner)
	{
		m_wpOwner = pOwner;
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

	void BoostTcpSocket::ReadMessage()
	{
	}

	void BoostTcpSocket::Start()
	{
	}

	void BoostTcpSocket::Write(const Message& msg)
	{
	}

	void BoostTcpSocket::Read()
	{
		boost::asio::async_read(m_socket,
			boost::asio::buffer(m_readMsg.Data(), Message::HEADER_SIZE),
			[this](boost::system::error_code error, std::size_t /*readSize*/)
		{
				if (error)
				{
					if (error == boost::asio::error::eof)
					{
						INFO_LOG("Socket disconnected ( ClientId - %d )", 0);
					}
					else
					{
						WARN_LOG("Socket error ( error - %d )", error.value());
					}

					if ( const auto pOwner = m_wpOwner.lock() )
					{
						pOwner->OnDisconnected();
					}
				}
				else
				{
					ReadMessage();
					Read();
				}
		});
	}

	ESocketType BoostTcpSocket::GetType()
	{
		return ESocketType::BOOST_TCP;
	}
	
	bool BoostTcpSocket::IsValid() const
	{
		if (!m_socket.is_open())
			return false;

		if (!m_wpOwner.lock())
			return false;

		return true;
	}
}
