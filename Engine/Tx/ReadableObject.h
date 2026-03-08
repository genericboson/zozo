#pragma once

#include <boost/asio.hpp>

namespace GenericBoson
{
	class CacheField;
	class CacheTx;

	namespace asio = boost::asio;

	class ReadableObject
	{
	public:
		ReadableObject(CacheTx& tx);

		bool Select();

		asio::awaitable<bool> Execute(DBResult& dbResult);

		std::string GetQuery(const std::string& wherePhrase = "");
	};
}
