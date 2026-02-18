#include "PCH.h"

#include <format>

#include "boost/algorithm/string/join.hpp"

#include "CacheField.h"
#include "CacheObject.h"

namespace GenericBoson
{
	template<typename CALLABLE>
	std::vector<std::string> CacheObject::GetFormattedBoundFieldStrings(const CALLABLE& callable)
	{
		const auto& fields = GetFields();

		std::vector<std::string> formattedFields;
		formattedFields.reserve(fields.size());
		for (const auto pField : fields)
		{
			NULL_CONTINUE(pField);
			if (!pField->IsBound())
				continue;
			
			callable(*pField);
		}

		return formattedFields;
	}

	std::string CacheObject::GetQuery( const QueryType queryType, const std::string& wherePhrase /*= ""*/)
	{
		switch ( queryType )
		{
		case QueryType::Insert:
		{
			if (!wherePhrase.empty())
			{
				ERROR_LOG("WHERE phrase is not applicable for INSERT queries.");
				return "";
			}

			const auto flaggeds = GetFormattedBoundFieldStrings(
				[](const CacheField& pField)
				{
					return pField.GetName();
				});

			const auto values = GetFormattedBoundFieldStrings(
				[](const CacheField& pField)
				{
					return pField.GetValueString();
				});

			const auto flaggedsStr = boost::algorithm::join(flaggeds, ",");
			const auto valuesStr   = boost::algorithm::join(values, ",");
			
			return std::format("INSERT INTO {} ({}) VALUES {};",
				GetObjectName(),
				flaggedsStr, valuesStr);
		}
		break;
		case QueryType::Update:
		{
			const auto pairs = GetFormattedBoundFieldStrings(
				[](const CacheField& pField)
				{
					return std::format("{} = {}", pField.GetName(), pField.GetValueString());
				});

			auto query = std::format("UPDATE {} SET {}",
				GetObjectName(), boost::algorithm::join(pairs, ","));

			if (wherePhrase.empty())
			{
				return std::format("{};", query);
			}

			return std::format("{} WHERE {};", query, wherePhrase);
		}
		break;
		case QueryType::Delete:
		{
			const auto pairs = GetFormattedBoundFieldStrings(
				[](const CacheField& pField)
				{
					return std::format("{} = {}", pField.GetName(), pField.GetValueString());
				});

			return std::format("DELETE FROM {} WHERE {};", 
				GetObjectName(), boost::algorithm::join(pairs, ","));
		}
		break;
		}
	}

	bool CacheObject::Insert()
	{
		m_queries.push_back(GetQuery(QueryType::Insert));
		return true;
	}

	bool CacheObject::Update()
	{
		m_queries.push_back(GetQuery(QueryType::Update));
		return true;
	}

	bool CacheObject::Delete()
	{
		m_queries.push_back(GetQuery(QueryType::Delete));
		return true;
	}

	bool CacheObject::Execute()
	{
		for (const auto& query : m_queries)
		{
			INFO_LOG("Executing query : {}", query);
			
			if (auto [dbErr] = co_await m_server.m_pDbConn->async_execute(
				queryStr,
				result,
				asio::as_tuple(asio::use_awaitable));
				dbErr)
			{
				ERROR_LOG("Query execute error. error code - {}({})", dbErr.value(), dbErr.message());
				co_return;
			}
		}
	}
}