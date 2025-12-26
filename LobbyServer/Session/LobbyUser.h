#pragma once

#include <Engine/Tx/TxExecutor.h>
#include <Engine/IActor.h>

#include "LobbyServer.h"

namespace GenericBoson
{
	class ISocket;

	namespace asio = boost::asio;

	class LobbyUser :
		public IActor,
		public TxExecutor,
		public std::enable_shared_from_this<LobbyUser>
	{
		friend class LobbyUserManager;

	public:
		LobbyUser(LobbyServer& lobbyServer, const std::shared_ptr<ISocket>& pSocket);
		virtual ~LobbyUser() = default;

		int64_t Id() const override;
		bool Initialize() override;

		void Write();
		asio::awaitable<void> Read(const uint8_t* pData, std::size_t dataSize) override;
	private:
		void OnDisconnected() override;
		void OnAccepted() override;

		void SendLoginAck();
	private:
		int64_t                  m_id;
		std::shared_ptr<ISocket> m_pSocket;
		LobbyServer&             m_server;
	};
}