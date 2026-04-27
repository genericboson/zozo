#pragma once

#include <memory>
#include <boost/asio.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/mysql.hpp>
#include <boost/mysql/connection_pool.hpp>
#include <boost/mysql/diagnostics.hpp>

#include "Engine/DB/DBManager.h"
#include "Engine/Tx/MemTx.h"
#include "Engine/Tx/MemField.h"
#include "Engine/Concepts.h"

namespace GenericBoson
{
	class MemField;
	class DBResult;

	namespace asio = boost::asio;
	namespace mysql = boost::mysql;

	class IMemObject
	{
		public:
		virtual ~IMemObject()                                                        = default;
		virtual asio::awaitable<bool> Execute(DBResult& dbResult)                      = 0;
																				       
		virtual auto GetObjectName() const -> std::string                              = 0;
		virtual auto GetFieldNames() const -> const std::vector<std::string> &         = 0;
		virtual auto GetFieldName(const int32_t fieldEnumValue) const -> std::string   = 0;
		virtual auto GetField(const std::string& fieldName) const -> const MemField* = 0;
		virtual auto GetField(const int32_t fieldEnumValue) const -> const MemField* = 0;
		virtual auto GetFields() const -> const std::vector<const MemField*> &       = 0;
	};

	template<typename T>
	class MemObject : 
		public T, 
		public IMemObject, 
		public std::enable_shared_from_this<MemObject<T>>
	{
		enum class WriteQueryType
		{
			Insert,
			Update,
			Delete
		};

	public:
		MemObject(MemTx& tx)
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

		virtual std::shared_ptr<IMemObject> CreateObject() { return nullptr; }

#pragma region Readable
		//=================================================================
		// Readable
		//=================================================================

		asio::awaitable<DBResult> Select(bool isAuto = true) requires ReadableLike<T>
		{
			DBResult dbResult{ .resultCode = Zozo::ResultCode::ResultCode_Success };
			m_queries.push_back(GetQuery());
			if (isAuto)
			{
				co_await ExecuteReadQuery(dbResult);
			}
			co_return dbResult;
		}

		asio::awaitable<bool> ExecuteReadQuery(DBResult& dbResult)
			requires ReadableLike<T>
		{
			auto opConn = co_await DBManager::GetInstance()->GetConnection();
			NULL_CO_RETURN(opConn, false);

			const auto joinedQuery = boost::algorithm::join(m_queries, "");

			mysql::results result;
			if(const auto [dbErr] = co_await (*opConn)->async_execute(
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
				auto pObj = std::static_pointer_cast<MemObject<T>>(CreateObject());
				NULL_CONTINUE(pObj);
				pObj->SetFields(row);
				dbResult.pChacheObjects.emplace_back(std::move(pObj));
			}

			co_return true;
		}

		bool SetFields(const mysql::row_view& row)
			requires ReadableLike<T>
		{
			const auto fieldNames = GetFieldNames();
			NULL_RETURN(!fieldNames.empty(), false);
			for (size_t i = 0; i < fieldNames.size(); ++i)
			{
				auto pField = const_cast<MemField*>(GetField(fieldNames[i]));
				NULL_CONTINUE(pField);

				try
				{
					pField->Set(row.at(i));
				}
				catch (boost::exception& except)
				{
					ERROR_LOG("Exception caught while setting field:{}, exception msg:{}", 
						fieldNames[i], boost::diagnostic_information(except));
				}
			}
			return true;
		}

		std::string GetQuery(const std::string& wherePhrase = "")
			requires ReadableLike<T>
		{
			const auto fieldNames = GetFieldNames();
			const auto fieldNamesStr = boost::algorithm::join(fieldNames,",");

			auto query = std::format("SELECT {} FROM zozo_game.{}",
				fieldNamesStr, GetObjectName());

			AttachWherePhrase(query, wherePhrase);
			return query;
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
					&MemField::IsBound,
					[](const MemField& pField)
					{
						return pField.GetName();
					});

				const auto values = GetFormattedFieldsString(
					&MemField::IsBound,
					[](const MemField& pField)
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
					&MemField::IsBound,
					[](const MemField& pField)
					{
						return std::format("{} = {}", pField.GetName(), pField.GetValueString());
					});

				auto query = std::format("UPDATE {} SET {}",
					GetObjectName(), pairs);

				AttachWherePhrase(query, wherePhrase);

				return query;
			}
			break;
			case WriteQueryType::Delete:
			{
				const auto keys = GetFormattedFieldsString(
					&MemField::IsKey,
					[](const MemField& pField)
					{
						return std::format("{} = {}", pField.GetName(), pField.GetValueString());
					});

				return std::format("DELETE FROM {} WHERE {};",
					GetObjectName(), keys);
			}
			break;
			}
		}

		asio::awaitable<DBResult> Insert(bool isAuto = true) requires WritableLike<T>
		{
			DBResult dbResult{ .resultCode = Zozo::ResultCode::ResultCode_Success };
			m_queries.push_back(GetQuery(WriteQueryType::Insert));
			if (isAuto)
			{
				co_await ExecuteWriteQuery(dbResult);
			}
			co_return dbResult;
		}

		asio::awaitable<DBResult> Update(bool isAuto = true) requires WritableLike<T>
		{
			DBResult dbResult{ .resultCode = Zozo::ResultCode::ResultCode_Success };
			m_queries.push_back(GetQuery(WriteQueryType::Update));
			if (isAuto)
			{
				co_await ExecuteWriteQuery(dbResult);
			}
			co_return dbResult;
		}

		asio::awaitable<DBResult> Delete(bool isAuto = true) requires WritableLike<T>
		{
			DBResult dbResult{ .resultCode = Zozo::ResultCode::ResultCode_Success };
			m_queries.push_back(GetQuery(WriteQueryType::Delete));
			if (isAuto)
			{
				co_await ExecuteWriteQuery(dbResult);
			}
			co_return dbResult;
		}

		asio::awaitable<bool> ExecuteWriteQuery(DBResult& dbResult)
			requires WritableLike<T>
		{
			auto opConn = co_await DBManager::GetInstance()->GetConnection();
			NULL_CO_RETURN(opConn, false);

			const auto joinedQuery = boost::algorithm::join(m_queries, "");

			mysql::results result;
			if(const auto [dbErr] = co_await (*opConn)->async_execute(
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
	protected:
		template<typename CALLABLE>
		std::string GetFormattedFieldsString(
			bool  (MemField::* FieldFunc)() const,
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

				formattedFields.push_back(callable(*pField));
			}

			return boost::algorithm::join(formattedFields, ",");
		}

	private:
		void AttachWherePhrase(std::string& query, const std::string& wherePhrase)
		{
			const auto keys = GetFormattedFieldsString(
				&MemField::IsKey,
				[](const MemField& pField)
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
		MemTx& m_tx;

		std::list<std::string> m_queries;
	};
}
