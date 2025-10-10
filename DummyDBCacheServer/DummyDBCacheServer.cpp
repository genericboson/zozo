#include "PCH.h"

#include <Engine/Socket/BoostTcpSocket.h>

#include "DummyDBCacheServer.h"

#include "Session/DBClient.h"
#include "Session/DBClientManager.h"

namespace GenericBoson
{
	DummyDBCacheServer::DummyDBCacheServer(int32_t port /*= 8003*/)
		: ServerBase(port)
	{
	}

	auto DummyDBCacheServer::CreateActor(const std::shared_ptr<ISocket>& pSocket)
		-> std::shared_ptr<IActor>
	{
		return std::make_shared<DBClient>(pSocket);
	}
}