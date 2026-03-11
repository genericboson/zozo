#pragma once

#include <boost/asio.hpp>

namespace GenericBoson
{
	class CacheField;
	class CacheTx;

	namespace asio = boost::asio;

	template<typename T>
	concept CacheObjectType = requires(T t)
	{
		{ t.GetObjectName() } -> std::convertible_to<std::string>;
		{ t.GetFieldNames() } -> std::convertible_to<const std::vector<std::string>&>;
		{ t.GetFieldName(0) } -> std::convertible_to<std::string>;
		{ t.GetField("") }    -> std::convertible_to<const CacheField*>;
		{ t.GetField(0) }     -> std::convertible_to<const CacheField*>;
		{ t.GetFields() }     -> std::convertible_to<const std::vector<const CacheField*>&>;
	};

	class CacheObject
	{
	public:
		CacheObject(CacheTx& tx);

		virtual asio::awaitable<bool> Execute(DBResult& dbResult) = 0;

	protected:
		virtual auto GetObjectName() const                            -> std::string                           = 0;
		virtual auto GetFieldNames() const                            -> const std::vector<std::string> &      = 0;
		virtual auto GetFieldName(const int32_t fieldEnumValue) const -> std::string                           = 0;
		virtual auto GetField(const std::string& fieldName) const     -> const CacheField*                     = 0;
		virtual auto GetField(const int32_t fieldEnumValue) const     -> const CacheField*                     = 0;
		virtual auto GetFields() const                                -> const std::vector<const CacheField*>& = 0;

		template<typename CALLABLE>
		std::string GetFormattedFieldsString(bool(CacheField::* FieldFunc)() const, const CALLABLE& callable);

	protected:
		CacheTx& m_tx;

		std::list<std::string> m_queries;
	};
}
