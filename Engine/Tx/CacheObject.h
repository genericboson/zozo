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
		virtual auto GetObjectName() -> std::string                      = 0;
		virtual auto GetFieldNames() -> const std::vector<std::string> & = 0;
	};
}
