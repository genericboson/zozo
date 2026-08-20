#pragma once

#include <boost/json.hpp>

namespace GenericBoson
{
	class IStaticData
	{
	public:
		virtual void Insert(const boost::json::object& obj) = 0;

		virtual std::shared_ptr<IStaticData> Create() = 0;
	};
}