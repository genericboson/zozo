#pragma once

#include <flatbuffers/flatbuffers.h>

#include <Engine/Singleton.h>
#include <Engine/Tx/Continuation.h>

namespace GenericBoson
{
	namespace Zozo { struct DBCacheLobbyMessage; }

	class DBCacheClient : public Singleton<DBCacheClient>
	{
	public:
		DBCacheClient() = default;
		virtual ~DBCacheClient() = default;

		auto Upsert(const flatbuffers::String& accountStr, const flatbuffers::String& passwordStr)
			-> boost::future<std::shared_ptr<flatbuffers::FlatBufferBuilder>>;
	private:
	};
}