#pragma once

#include <boost/asio.hpp>

namespace GenericBoson
{
	class CacheField;
	class CacheTx;

	namespace asio = boost::asio;

	class CacheObject
	{
		enum class QueryType
		{
			Select,
			Insert,
			Update,
			Delete
		};

	public:
		CacheObject(CacheTx& tx);

		bool Select();
		bool Insert();
		bool Update();
		bool Delete();

		asio::awaitable<bool> Execute();

	protected:
		virtual auto GetObjectName() const                            -> std::string                           = 0;
		virtual auto GetFieldNames() const                            -> const std::vector<std::string> &      = 0;
		virtual auto GetFieldName(const int32_t fieldEnumValue) const -> std::string                           = 0;
		virtual auto GetField(const std::string& fieldName) const     -> const CacheField*                     = 0;
		virtual auto GetField(const int32_t fieldEnumValue) const     -> const CacheField*                     = 0;
		virtual auto GetFields() const                                -> const std::vector<const CacheField*>& = 0;

	private:
		template<typename CALLABLE>
		std::vector<std::string> GetFormattedBoundFieldStrings(const CALLABLE& callable);

		std::string GetQuery(const QueryType queryType, const std::string& wherePhrase = "");

	private:
		CacheTx& m_tx;

		std::list<std::string> m_queries;
	};
}
