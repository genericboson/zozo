#include "PCH.h"

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

	awaitable<void> BoostTcpSocket::Write(const Message& msg)
	{
		co_return;
	}

	awaitable<void> BoostTcpSocket::Read()
	{
		try
		{
			auto readHeaderSize = co_await async_read(m_socket,
				boost::asio::buffer(m_readMsg.Data(), Message::HEADER_SIZE),
				boost::asio::use_awaitable);

			if (readHeaderSize && m_readMsg.DecodeHeader())
			{
				auto readBodySize = co_await async_read(m_socket,
					boost::asio::buffer(m_readMsg.Body(), m_readMsg.BodySize()),
					boost::asio::use_awaitable);

				if (const auto pOwner = m_wpOwner.lock();
					readBodySize && pOwner)
				{
					pOwner->Read(m_readMsg.Body(), m_readMsg.BodySize());
				}
				else
				{
					ERROR_LOG("Invalid Socket State or pOwner is nullptr. readBodySize - {}", readBodySize);
				}
			}
		}
		catch (const boost::system::system_error& e)
		{
			if (e.code() == error::eof)
			{
				INFO_LOG("Socket disconnected");
			}
			else
			{
				ERROR_LOG("Socket error ( error - {} )", e.code().message());
			}

			if (const auto pOwner = m_wpOwner.lock())
			{
				pOwner->OnDisconnected();
			}
		}
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
