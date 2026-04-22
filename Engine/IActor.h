#pragma once

#include <boost/asio/awaitable.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/strand.hpp>

namespace GenericBoson
{
	namespace asio = boost::asio;

	class IActor
	{
	public:
		virtual ~IActor() = default;
		virtual int64_t Id() const = 0;

		virtual void OnDisconnected() = 0;
		virtual void OnAccepted() = 0;
		
		virtual bool Initialize() = 0;

		virtual asio::awaitable<void> Update() = 0;
		virtual int64_t GetUpdatePeriodMs() const = 0;

		virtual asio::awaitable<void> Read(const uint8_t* pData, std::size_t dataSize) = 0;

		virtual asio::strand<asio::io_context::executor_type> GetStrand() const = 0;
	};
}