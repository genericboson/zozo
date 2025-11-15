#pragma once

#include <Engine/IActor.h>

#include "GameServer.h"

namespace GenericBoson
{
	class GameServer;

	class LobbyProxy : public IActor
	{
	public:
		LobbyProxy(GameServer& server);

		// Inherited via IActor
		int64_t Id() const override;
		void OnDisconnected() override;
		void OnAccepted() override;
		bool Initialize() override;

		asio::awaitable<void> Read(const uint8_t* pData, std::size_t dataSize) override;

	private:

		GameServer& m_server;
	};
}