#pragma once

#include <Engine/Singleton.h>

namespace GenericBoson
{
	class DBCacheClient : public Singleton<DBCacheClient>
	{
	public:
		DBCacheClient() = default;
		virtual ~DBCacheClient() = default;
	private:
	};
}