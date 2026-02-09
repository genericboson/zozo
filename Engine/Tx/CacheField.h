#pragma once

namespace GenericBoson
{
	class CacheField
	{
	public:
		virtual std::string GetName() const = 0;
		virtual bool IsFlagged() const = 0;
	};
}
