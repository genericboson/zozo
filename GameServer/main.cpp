#include "PCH.h"

#include "GameServer.h"

int main()
{
	using namespace GenericBoson;

	GameServer server;

	if (!server.Start())
		return -1;

	static_cast< void >(getchar());

	server.Stop();

	return 0;
}