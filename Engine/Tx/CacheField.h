#pragma once

namespace GenericBoson
{
	class CacheField
	{
	public:
		virtual std::string GetName()        const = 0;
		virtual std::string GetValueString() const = 0;
		virtual bool IsBound() const = 0;
	};
}
