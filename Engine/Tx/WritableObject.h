#pragma once

#include <boost/asio.hpp>

#include "CacheObject.h"

namespace GenericBoson
{
	class CacheField;
	class CacheTx;

	namespace asio = boost::asio;

	class WritableObject : public CacheObject
	{
		enum class QueryType
		{
			Insert,
			Update,
			Delete
		};

	public:
		WritableObject(CacheTx& tx);

		bool Insert();
		bool Update();
		bool Delete();

		asio::awaitable<bool> Execute(DBResult& dbResult);

		std::string GetQuery(const QueryType queryType, const std::string& wherePhrase = "");
	};
}
