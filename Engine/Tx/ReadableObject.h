#pragma once

#include <boost/asio.hpp>

#include "CacheObject.h"

namespace GenericBoson
{
	class CacheField;
	class CacheTx;

	namespace asio = boost::asio;

	template<CacheObjectType T>
	class ReadableObject : T
	{
	public:
		ReadableObject(CacheTx& tx);

		bool Select();

		asio::awaitable<bool> Execute(DBResult& dbResult);

		std::string GetQuery(const std::string& wherePhrase = "");
	};
}
