#pragma once

#include <boost/asio.hpp>
#include <boost/mysql.hpp>
#include <boost/algorithm/string/join.hpp>

#include "Engine/Tx/CacheTx.h"
#include "Engine/Tx/CacheField.h"
#include "Engine/Concepts.h"

namespace GenericBoson
{
	class CacheField;
	class DBResult;

	namespace asio = boost::asio;
	namespace mysql = boost::mysql;

	class ICacheObject
	{
		public:
		virtual ~ICacheObject()                                                        = default;
		virtual asio::awaitable<bool> Execute(DBResult& dbResult)                      = 0;
																				       
		virtual auto GetObjectName() const -> std::string                              = 0;
		virtual auto GetFieldNames() const -> const std::vector<std::string> &         = 0;
		virtual auto GetFieldName(const int32_t fieldEnumValue) const -> std::string   = 0;
		virtual auto GetField(const std::string& fieldName) const -> const CacheField* = 0;
		virtual auto GetField(const int32_t fieldEnumValue) const -> const CacheField* = 0;
		virtual auto GetFields() const -> const std::vector<const CacheField*> &       = 0;
	};

	template<typename T>
	class CacheObject : 
		public T, 
		public ICacheObject, 
		public std::enable_shared_from_this<CacheObject<T>>
	{
		enum class WriteQueryType
		{
			Insert,
			Update,
			Delete
		};

	public:
		CacheObject(CacheTx& tx)
			: m_tx(tx)
		{}

		virtual asio::awaitable<bool> Execute(DBResult& dbResult) override
		{
			if constexpr (ReadableLike<T>)
			{
				co_return co_await ExecuteReadQuery(dbResult);
			}
			else if constexpr (WritableLike<T>)
			{
				co_return co_await ExecuteWriteQuery(dbResult);
			}
			else
			{
				static_assert(ReadableLike<T> || WritableLike<T>, 
					"T must be either Readable or Writable.");
				co_return false;
			}
		}

#pragma region Readable
		//=================================================================
		// Readable
		//=================================================================

		bool Select() requires ReadableLike<T>
		{
			m_queries.push_back(GetQuery());
			return true;
		}

		asio::awaitable<bool> ExecuteReadQuery(DBResult& dbResult)
			requires ReadableLike<T>
		{
			// #todo - compress queries
			const auto joinedQuery = boost::algorithm::join(m_queries, "");

			mysql::results result;
			if (auto [dbErr] = co_await m_tx.GetExecutor().GetDbConnection().async_execute(
				joinedQuery,
				result,
				asio::as_tuple(asio::use_awaitable));
				dbErr)
			{
				ERROR_LOG("Query execute error. error code - {}({})", dbErr.value(), dbErr.message());
				co_return false;
			}

			if (result.rows().empty())
			{
				dbResult.resultCode = Zozo::ResultCode::ResultCode_NoData;
				co_return true;
			}

			for (const auto& row : result.rows())
			{
				const auto pObj = std::make_shared<CacheObject<T>>(*this);
				pObj->PopulateFieldsFromRow(row);
				dbResult.pChacheObjects.emplace_back(std::move(pObj));
			}

			co_return true;
		}

		asio::awaitable<bool> PopulateFieldsFromRow(const mysql::row_view& row)
			requires ReadableLike<T>
		{
			const auto fieldNames = GetFieldNames();
			for (size_t i = 0; i < fieldNames.size(); ++i)
			{
				const auto pField = GetField(fieldNames[i]);
				NULL_CONTINUE(pField);
				pField->SetValueFromString(row.at(i).as_string());
			}
			co_return true;
		}

		std::string GetQuery(const std::string& wherePhrase = "")
			requires ReadableLike<T>
		{
			const auto fieldNames = GetFieldNames();
			const auto fieldNamesStr = boost::algorithm::join(fieldNames, ",");

			auto query = std::format("SELECT {} FROM {}",
				fieldNamesStr, GetObjectName());

			AttachWherePhrase(query, wherePhrase);
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

				auto query = std::format("UPDATE {} SET {}",
					GetObjectName(), pairs);

				AttachWherePhrase(query, wherePhrase);
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

		asio::awaitable<bool> ExecuteWriteQuery(DBResult& dbResult)
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
		std::string GetFormattedFieldsString(
			bool  (CacheField::* FieldFunc)() const,
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

	private:
		void AttachWherePhrase(std::string& query, const std::string& wherePhrase)
		{
			const auto keys = GetFormattedFieldsString(
				&CacheField::IsKey,
				[](const CacheField& pField)
				{
					return std::format("{} = {}", pField.GetName(), pField.GetValueString());
				});

			if (keys.empty())
			{
				if (wherePhrase.empty())
				{
					return;
				}

				query = std::format("{} WHERE {};", query, wherePhrase);
				return;
			}
			else if (wherePhrase.empty())
			{
				query = std::format("{} WHERE {};", query, keys);
				return;
			}

			query = std::format("{} WHERE {} AND {};", query, wherePhrase, keys);
		}

	protected:
		CacheTx& m_tx;

		std::list<std::string> m_queries;
	};
}
