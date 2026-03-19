#pragma once

#include <boost/algorithm/string/join.hpp>
#include <boost/asio.hpp>
#include <boost/mysql.hpp>
#include <format>

#include "CacheObject.h"
#include "CacheField.h"
#include "CacheTx.h"
#include "Engine/Types.h"
#include "TxExecutor.h"

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

	template<typename T>
	Readable<T>::Readable(CacheTx& tx)
		: T(tx)
	{
	}

	template<typename T>
	std::string Readable<T>::GetQuery(const std::string& wherePhrase /*= ""*/)
	{
		const auto fieldNames = T::GetFieldNames();
		const auto fieldNamesStr = boost::algorithm::join(fieldNames, ",");

		const auto keys = T::GetFormattedFieldsString(
			&CacheField::IsKey,
			[](const CacheField& pField)
			{
				return std::format("{} = {}", pField.GetName(), pField.GetValueString());
			});

		auto query = std::format("SELECT {} FROM {}",
			fieldNamesStr, T::GetObjectName());

		if (wherePhrase.empty())
		{
			return std::format("{} WHERE {};", query, keys);
		}
		return std::format("{} WHERE {} AND {};", query, wherePhrase, keys);
	}

	template<typename T>
	bool Readable<T>::Select()
	{
		T::m_queries.push_back(GetQuery());
		return true;
	}

	template<typename T>
	asio::awaitable<bool> Readable<T>::Execute(DBResult& dbResult)
	{
		// #todo - compress queries
		const auto joinedQuery = boost::algorithm::join(T::m_queries, "");

		mysql::results result;
		if (auto [dbErr] = co_await T::m_tx.GetExecutor().GetDbConnection().async_execute(
			joinedQuery,
			result,
			asio::as_tuple(asio::use_awaitable));
			dbErr)
		{
			ERROR_LOG("Query execute error. error code - {}({})", dbErr.value(), dbErr.message());
			co_return false;
		}

		co_return true;
	}
}
