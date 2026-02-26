#include "PCH.h"

#include <format>

#include "boost/algorithm/string/join.hpp"

#include "CacheField.h"
#include "CacheObject.h"
#include "CacheTx.h"
#include "TxExecutor.h"

namespace GenericBoson
{
	CacheObject::CacheObject(CacheTx& tx)
		: m_tx(tx)
	{
	}

	template<typename CALLABLE>
	std::string CacheObject::GetFormattedFieldsString(
		bool  (CacheField::*FieldFunc)() const, 
		const CALLABLE& callable)
	{
		const auto& fields = GetFields();

		std::vector<std::string> formattedFields;
		formattedFields.reserve(fields.size());
		for (const auto pField : fields)
		{
			NULL_CONTINUE(pField);
			if (!std::invoke(FieldFunc, *pField))
				continue;
			
			callable(*pField);
		}

		return boost::algorithm::join(formattedFields, ",");
	}

	std::string CacheObject::GetQuery( const QueryType queryType, const std::string& wherePhrase /*= ""*/)
	{
		switch ( queryType )
		{
		case QueryType::Select:
		{
			const auto fieldNames = GetFieldNames();
			const auto fieldNamesStr = boost::algorithm::join(fieldNames, ",");

			const auto keys = GetFormattedFieldsString(
				&CacheField::IsKey,
				[](const CacheField& pField)
				{
					return std::format("{} = {}", pField.GetName(), pField.GetValueString());
				});
			
			auto query = std::format("SELECT {} FROM {}",
				fieldNamesStr, GetObjectName());

			if (wherePhrase.empty())
			{
				return std::format("{} WHERE {};", query, keys);
			}
			return std::format("{} WHERE {} AND {};", query, wherePhrase, keys);
		}
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

	bool CacheObject::Select()
	{
		m_queries.push_back(GetQuery(QueryType::Select));
		return true;
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

	asio::awaitable<bool> CacheObject::Execute()
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