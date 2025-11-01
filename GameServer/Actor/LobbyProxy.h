#pragma once

#include <Engine/IActor.h>

namespace GenericBoson
{
	class LobbyProxy : public IActor
	{
		// Inherited via IActor
		int64_t Id() const override;
		void OnDisconnected() override;
		void OnAccepted() override;
		bool Initialize() override;

		asio::awaitable<void> Read(const uint8_t* pData, std::size_t dataSize) override;
	};
}