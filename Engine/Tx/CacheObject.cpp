#include "PCH.h"

#include <format>

#include "boost/algorithm/string/join.hpp"

#include "CacheField.h"
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
			auto valuesSize = 0;
			const auto flaggeds = boost::algorithm::join_if(GetFieldNames(), ",", [this, &valuesSize](const std::string& fieldName) {
					if (GetField(fieldName)->IsBound())
					{
						++valuesSize;
						return true;
					}
					return false;
				});

			std::vector<std::string> values;
			values.reserve(valuesSize);
			std::ranges::transform(GetFieldNames(), std::back_inserter(values), 
				[this](const std::string& fieldName) { 
					const auto pField = GetField(fieldName);
					NULL_RETURN(pField, std::string{});
					return pField->GetValueString();
				});

			const auto valuesStr = boost::algorithm::join(values, ",");

			query = std::format("INSERT INTO {} ({}) VALUES ({});",
				GetObjectName(),
				flaggeds, valuesStr);
		}
			break;
		case QueryType::UPDATE:
			query = "UPDATE TableName SET ";
			for ( const auto & name : GetFieldNames() )
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