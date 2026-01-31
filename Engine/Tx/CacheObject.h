#pragma once

namespace GenericBoson
{
	class CacheObject
	{
	protected:
		virtual auto GetNames() -> std::vector<std::string> = 0;
	};
}
