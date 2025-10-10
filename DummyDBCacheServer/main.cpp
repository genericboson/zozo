#include "PCH.h"

#include "DummyDBCacheServer.h"

int main()
{
	using namespace GenericBoson;

	DummyDBCacheServer server;

	if (!server.Start())
		return -1;

	static_cast<void>(getchar());

	server.Stop();

	return 0;
}