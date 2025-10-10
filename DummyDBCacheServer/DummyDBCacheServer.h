#pragma once

#include <boost/asio.hpp>

#include <Engine/Socket/ServerBase.h>

namespace GenericBoson
{
	class DummyDBCacheServer : public ServerBase
	{
	public:
		DummyDBCacheServer(int32_t port = 8003);
		virtual ~DummyDBCacheServer() = default;

		auto CreateActor(const std::shared_ptr<ISocket>& pSocket)
			-> std::shared_ptr<IActor> override;
	};
}