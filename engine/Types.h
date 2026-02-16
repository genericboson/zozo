#pragma once

#include <boost/asio.hpp>

#include <MessageSchema/Common/Constant_generated.h>

namespace GenericBoson
{
	namespace asio = boost::asio;

	struct DBResult
	{
		Zozo::ResultCode resultCode;
	};

	using CacheTxPreCallback = std::function<asio::awaitable<bool>(void)>;
	using CacheTxPostCallback = std::function<asio::awaitable<bool>(DBResult)>;
}