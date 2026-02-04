#include "PCH.h"

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
			std::vector<std::string> names;
			names.reserve(GetFieldNames().size());

			query = "INSERT INTO TableName (";
			for (const auto& name : GetFieldNames())
			{
				if(name.)

				query += name + ", ";
			}
			query = query.substr(0, query.size() - 2); // Remove last comma
			query += ") VALUES (";
			for (size_t i = 0; i < GetNames().size(); ++i)
			{
				query += "?, ";
			}
			query = query.substr(0, query.size() - 2); // Remove last comma
			query += ");";
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