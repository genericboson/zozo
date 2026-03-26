#pragma once

#include <boost/asio.hpp>
#include <boost/mysql.hpp>
#include <boost/algorithm/string/join.hpp>

#include "CacheField.h"
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
		enum class WriteQueryType
		{
			Insert,
			Update,
			Delete
		};

	public:
		CacheObject(CacheTx& tx);

#pragma region Readable
		//=================================================================
		// Readable
		//=================================================================

		bool Select() requires ReadableLike<T>
		{
			T::m_queries.push_back(GetQuery());
			return true;
		}

		asio::awaitable<bool> Execute(DBResult& dbResult)
			requires ReadableLike<T>
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
			requires ReadableLike<T>
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
#pragma endregion Readable


#pragma region Writable
		//=================================================================
		// Writable
		//=================================================================

		std::string GetQuery(const WriteQueryType queryType, const std::string& wherePhrase /*= ""*/)
			requires WritableLike<T>
		{
			switch (queryType)
			{
			case WriteQueryType::Insert:
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
			case WriteQueryType::Update:
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
			case WriteQueryType::Delete:
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

		bool Insert() requires WritableLike<T>
		{
			m_queries.push_back(GetQuery(WriteQueryType::Insert));
			return true;
		}

		bool Update() requires WritableLike<T>
		{
			m_queries.push_back(GetQuery(WriteQueryType::Update));
			return true;
		}

		bool Delete() requires WritableLike<T>
		{
			m_queries.push_back(GetQuery(WriteQueryType::Delete));
			return true;
		}

		asio::awaitable<bool> Execute(DBResult& dbResult)
			requires WritableLike<T>
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

#pragma endregion Writable

	public:
		virtual auto GetFields() const -> const std::vector<const CacheField*> & = 0;
		virtual auto GetObjectName() const -> std::string = 0;

	protected:
		template<typename CALLABLE>
		std::string GetFormattedFieldsString(bool(CacheField::* FieldFunc)() const, const CALLABLE& callable);

	protected:
		CacheTx& m_tx;

		std::list<std::string> m_queries;
	};
}
