#pragma once

#include <boost/asio.hpp>
#include <format>

#include "boost/algorithm/string/join.hpp"

#include "CacheField.h"
#include "CacheObject.h"
#include "CacheTx.h"
#include "Types.h"
#include "TxExecutor.h"

namespace GenericBoson
{
	class CacheField;
	class CacheTx;

	namespace asio = boost::asio;

	template<typename T>
	class WritableObject : public T
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

	template<typename T>
	WritableObject<T>::WritableObject(CacheTx& tx)
		: T(tx)
	{
	}

	template<typename T>
	std::string WritableObject<T>::GetQuery(const QueryType queryType, const std::string& wherePhrase /*= ""*/)
	{
		switch (queryType)
		{
		case QueryType::Insert:
		{
			if (!wherePhrase.empty())
			{
				ERROR_LOG("WHERE phrase is not applicable for INSERT queries.");
				return "";
			}

			const auto flaggeds = GetFormattedFieldsString(
				&CacheField::IsBound,
				[](const CacheField& pField)
				{
					return pField.GetName();
				});

			const auto values = GetFormattedFieldsString(
				&CacheField::IsBound,
				[](const CacheField& pField)
				{
					return pField.GetValueString();
				});

			return std::format("INSERT INTO {} ({}) VALUES {};",
				GetObjectName(),
				flaggeds, values);
		}
		break;
		case QueryType::Update:
		{
			const auto pairs = GetFormattedFieldsString(
				&CacheField::IsBound,
				[](const CacheField& pField)
				{
					return std::format("{} = {}", pField.GetName(), pField.GetValueString());
				});

			const auto keys = GetFormattedFieldsString(
				&CacheField::IsKey,
				[](const CacheField& pField)
				{
					return std::format("{} = {}", pField.GetName(), pField.GetValueString());
				});

			auto query = std::format("UPDATE {} SET {}",
				GetObjectName(), pairs);

			if (wherePhrase.empty())
			{
				return std::format("{} WHERE {};", query, keys);
			}

			return std::format("{} WHERE {} AND {};", query, wherePhrase, keys);
		}
		break;
		case QueryType::Delete:
		{
			const auto keys = GetFormattedFieldsString(
				&CacheField::IsKey,
				[](const CacheField& pField)
				{
					return std::format("{} = {}", pField.GetName(), pField.GetValueString());
				});

			return std::format("DELETE FROM {} WHERE {};",
				GetObjectName(), keys);
		}
		break;
		}
	}

	template<typename T>
	bool WritableObject<T>::Insert()
	{
		m_queries.push_back(GetQuery(QueryType::Insert));
		return true;
	}

	template<typename T>
	bool WritableObject<T>::Update()
	{
		m_queries.push_back(GetQuery(QueryType::Update));
		return true;
	}

	template<typename T>
	bool WritableObject<T>::Delete()
	{
		m_queries.push_back(GetQuery(QueryType::Delete));
		return true;
	}

	template<typename T>
	asio::awaitable<bool> WritableObject<T>::Execute(DBResult& dbResult)
	{
		// #todo - compress queries
		const auto joinedQuery = boost::algorithm::join(m_queries, "");

		mysql::results result;
		if (auto [dbErr] = co_await m_tx.m_executor.m_dbConn.async_execute(
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
