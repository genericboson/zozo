#include "PCH.h"

#include "GameServer.h"

int main()
{
	using namespace GenericBoson;

	auto pServer = GameServer::CreateGameServer(8001);

	if (!pServer->Start())
		return -1;

	static_cast< void >(getchar());

	pServer->Stop();

	return 0;
}