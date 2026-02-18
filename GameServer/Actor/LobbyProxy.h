#pragma once

#include <Engine/EnvironmentVariable.h>
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

		asio::awaitable<void> Update() override { co_await CO_SLEEP_MS(1); };
		int64_t GetUpdatePeriodMs() const override { return Environment::GetDefaultUpdatePeriodMs(); };

		asio::awaitable<void> Read(const uint8_t* pData, std::size_t dataSize) override;

	private:

		GameServer& m_server;
	};
}