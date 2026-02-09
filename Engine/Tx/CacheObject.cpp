#include "PCH.h"

#include <format>

#include "boost/algorithm/string/join.hpp"

#include "CacheObject.h"

namespace GenericBoson
{
	std::string CacheObject::GetQuery( const QueryType queryType )
	{
		std::string query;
		switch ( queryType )
		{
		case QueryType::INSERT:
		{
			const auto& flaggeds = boost::algorithm::join_if(GetFieldNames(), ",", []() {
					return 
				});

			query = std::format("INSERT INTO {} ({}) VALUES ({});", 
				GetObjectName(), 
				flaggeds, ","), 
				"");
		}
			break;
		case QueryType::UPDATE:
			query = "UPDATE TableName SET ";
			for ( const auto & name : GetNames() )
			{
				query += name + " = ?, ";
			}
			query = query.substr( 0, query.size() - 2 ); // Remove last comma
			query += " WHERE id = ?;";
			break;
		case QueryType::DELETE:
			query = "DELETE FROM TableName WHERE id = ?;";
			break;
		}
		return query;
	}
}