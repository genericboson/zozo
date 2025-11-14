#include "PCH.h"

#include "LobbyServer.h"

int main()
{
	using namespace GenericBoson;

	LobbyServer externalServer{ LobbyServer::ELobbyServerSort::EXTERNAL };

	if (!externalServer.Start())
		return -1;

	LobbyServer internalServer{ LobbyServer::ELobbyServerSort::INTERNAL };

	if (!internalServer.Start())
		return -1;

	static_cast< void >(getchar());

	internalServer.Stop();
	externalServer.Stop();

	return 0;
}