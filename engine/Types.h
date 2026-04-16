#pragma once

#include <boost/asio.hpp>

#include <MessageSchema/Common/Constant_generated.h>

namespace GenericBoson
{
	namespace asio = boost::asio;

	class IMemObject;

	struct DBResult
	{
		Zozo::ResultCode resultCode;

		std::vector<std::shared_ptr<IMemObject>> pChacheObjects;
	};

	using MemTxPreCallback = std::function<asio::awaitable<bool>(void)>;
	using MemTxPostCallback = std::function<asio::awaitable<bool>(DBResult)>;
}