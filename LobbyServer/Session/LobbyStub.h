#pragma once

#include <Engine/EnvironmentVariable.h>
#include <Engine/Tx/TxExecutor.h>
#include <Engine/IActor.h>

#include "LobbyServer.h"

namespace GenericBoson
{
	class ISocket;
	class LobbyStubManager;

	namespace asio = boost::asio;

	class LobbyStub :
		public IActor,
		public TxExecutor,
		public std::enable_shared_from_this<LobbyStub>
	{
		friend class LobbyStubManager;

	public:
		LobbyStub( 
			LobbyServer& lobbyServer,
			const std::shared_ptr<ISocket>& pSocket);

		virtual ~LobbyStub() = default;

		int64_t Id() const override;
		bool Initialize() override;

		asio::awaitable<void> Update() override { co_await CO_SLEEP_MS(1); };
		int64_t GetUpdatePeriodMs() const override { return Environment::GetDefaultUpdatePeriodMs(); };

		void Write(const uint8_t* data, size_t size);
		asio::awaitable<void> Read(const uint8_t* pData, std::size_t dataSize) override;
	private:
		void OnDisconnected() override;
		void OnAccepted() override;
	private:
		int64_t                  m_id = 0;
		std::string              m_name, m_ip, m_port;
		std::atomic_int32_t      m_currentCCU = 0, m_maxCCU = 0;

		std::shared_ptr<ISocket> m_pSocket;
		LobbyServer& m_server;
	};
}