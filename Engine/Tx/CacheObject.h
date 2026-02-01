#pragma once

namespace GenericBoson
{
	class CacheObject
	{
	protected:
		virtual auto GetNames() -> const std::vector<std::string>& = 0;

	public:
		
	};
}
