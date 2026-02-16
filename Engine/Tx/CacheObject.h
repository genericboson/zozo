#pragma once

namespace GenericBoson
{
	class CacheField;

	class CacheObject
	{
		enum class QueryType
		{
			Insert,
			Update,
			Delete
		};

	public:
		bool Insert();
		bool Update();
		bool Delete();

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
		std::list<std::string> m_queries;
	};
}
