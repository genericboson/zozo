#pragma once

#include <boost/asio.hpp>
#include <boost/mysql.hpp>

#include "Engine/Concepts.h"

namespace GenericBoson
{
	class CacheField;
	class CacheTx;
	class DBResult;

	namespace asio = boost::asio;
	namespace mysql = boost::mysql;

	//template<typename T>
	//concept CacheObjectType = requires(T t)
	//{
		//{ t.GetObjectName() } -> std::convertible_to<std::string>;
		//{ t.GetFieldNames() } -> std::convertible_to<const std::vector<std::string>&>;
		//{ t.GetFieldName(0) } -> std::convertible_to<std::string>;
		//{ t.GetField("") }    -> std::convertible_to<const CacheField*>;
		//{ t.GetField(0) }     -> std::convertible_to<const CacheField*>;
		//{ t.GetFields() }     -> std::convertible_to<const std::vector<const CacheField*>&>;
	//};

	template<typename T>
	class CacheObject : public T
	{
	public:
		CacheObject(CacheTx& tx);

		// Readable

		bool Select() requires IsDerivedFromReadable<T>
		{
			T::m_queries.push_back(GetQuery());
			return true;
		}

		asio::awaitable<bool> Execute(DBResult& dbResult)
			requires IsDerivedFromReadable<T>
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

		std::string GetQuery(const std::string& wherePhrase = "")
			requires IsDerivedFromReadable<T>
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

	protected:
		template<typename CALLABLE>
		std::string GetFormattedFieldsString(bool(CacheField::* FieldFunc)() const, const CALLABLE& callable);

		auto GetFields() const -> const std::vector<const CacheField*>& = 0;

	protected:
		CacheTx& m_tx;

		std::list<std::string> m_queries;
	};
}
