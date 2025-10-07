#include "PCH.h"

#include "LobbyServer.h"

int main()
{
	using namespace GenericBoson;

	LobbyServer server;

	if (!server.Start())
		return -1;

	static_cast< void >(getchar());

	server.Stop();

	return 0;
}