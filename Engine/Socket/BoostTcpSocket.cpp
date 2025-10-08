#include "PCH.h"

#include "BoostTcpSocket.h"

namespace GenericBoson
{
	BoostTcpSocket::BoostTcpSocket(
		boost::asio::ip::tcp::socket pSocket)
		: m_socket(std::move(pSocket)),
		m_writeChannel{ m_socket.get_executor(), WRITE_CHANNEL_SIZE }
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

	bool BoostTcpSocket::IsSucceeded(boost::system::error_code errorCode) const
	{
		if (errorCode == boost::system::errc::success)
			return true;

		if (errorCode == error::eof)
		{
			INFO_LOG("Socket disconnected in write");
		}
		else if (errorCode != error::operation_aborted)
		{
			ERROR_LOG("Socket write error ( code - {}({}) )",
				errorCode.value(), errorCode.message());
		}

		if (const auto pOwner = m_wpOwner.lock())
		{
			pOwner->OnDisconnected();
		}

		return false;
	}

	awaitable<void> BoostTcpSocket::Write()
	{
		auto [receiveError, msg] = co_await m_writeChannel.async_receive(
			as_tuple(use_awaitable));

		if (!IsSucceeded(receiveError))
			co_return;

		auto [writeError, writeSize] = co_await m_socket.async_write_some(
			boost::asio::buffer(msg.Data(), msg.Length()),
			as_tuple(use_awaitable));

		if (!IsSucceeded(writeError))
			co_return;

		assert(writeSize == msg.Length());
	}

	awaitable<void> BoostTcpSocket::Read()
	{
		auto [readHeaderError,readHeaderSize] = co_await async_read(m_socket,
			boost::asio::buffer(m_readMsg.Data(), Message::HEADER_SIZE),
			as_tuple(use_awaitable));

		if (!IsSucceeded(readHeaderError))
			co_return;

		if (readHeaderSize && m_readMsg.DecodeHeader())
		{
			auto [readBodyError,readBodySize] = co_await async_read(m_socket,
				boost::asio::buffer(m_readMsg.Body(), m_readMsg.BodySize()),
				as_tuple(use_awaitable));

			if (!IsSucceeded(readBodyError))
				co_return;

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

	void BoostTcpSocket::EnqueueMessage(
		const uint8_t* pBuffer, 
		std::size_t bufferSize)
	{
		Message msg;
		msg.BodySize(bufferSize);
		msg.EncodeHeader();

		// #todo - remove memcpy
		if (const auto err = memcpy_s(msg.Body(), Message::MAX_BODY_SIZE, pBuffer, bufferSize);
			err != 0)
		{
			ERROR_LOG("memcpy_s failed. err - {}", err);
			return;
		}

		m_writeChannel.async_send(
			{},
			std::move(msg),
			[](boost::system::error_code) {});
	}
}
