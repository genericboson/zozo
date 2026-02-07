#pragma once

namespace GenericBoson
{
	enum class QueryType
	{
		INSERT,
		UPDATE,
		DELETE
	};

	class CacheObject
	{
	public:
		std::string GetQuery( const QueryType queryType );

	protected:
		virtual auto GetObjectName() -> const std::string &              = 0;
		virtual auto GetFieldNames() -> const std::vector<std::string> & = 0;
		virtual bool IsFlagged(const int64_t field)                      = 0;
	};
}
