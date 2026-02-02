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
		virtual auto GetNames() -> const std::vector<std::string> & = 0;
	};
}
