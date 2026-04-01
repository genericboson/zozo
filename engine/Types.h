#pragma once

#include <boost/asio.hpp>

#include <MessageSchema/Common/Constant_generated.h>

namespace GenericBoson
{
	namespace asio = boost::asio;

	class ICacheObject;

	struct DBResult
	{
		Zozo::ResultCode resultCode;

		std::vector<std::shared_ptr<ICacheObject>> pChacheObjects;
	};

	using CacheTxPreCallback = std::function<asio::awaitable<bool>(void)>;
	using CacheTxPostCallback = std::function<asio::awaitable<bool>(DBResult)>;
}