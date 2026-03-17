#pragma once

#include <boost/asio.hpp>

#include "CacheObject.h"

namespace GenericBoson
{
	class CacheField;
	class CacheTx;

	namespace asio = boost::asio;
	namespace mysql = boost::mysql;

	template<typename T>
	class Readable : public T
	{
	public:
		Readable(CacheTx& tx);

		bool Select();

		asio::awaitable<bool> Execute(DBResult& dbResult);

		std::string GetQuery(const std::string& wherePhrase = "");
	};
}
