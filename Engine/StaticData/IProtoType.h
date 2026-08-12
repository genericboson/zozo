#pragma once

namespace GenericBoson
{
	class IStaticData
	{
	public:
		virtual void Insert(const boost::json::object& obj) = 0;
	};
}