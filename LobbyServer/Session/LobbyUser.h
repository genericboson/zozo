#pragma once

#include <Engine/Tx/TxExecutor.h>
#include <Engine/IActor.h>

namespace GenericBoson
{
	class ISocket;

	class LobbyUser :
		public IActor,
		public TxExecutor,
		public std::enable_shared_from_this<LobbyUser>
	{
	public:
		LobbyUser(const std::shared_ptr<ISocket>& pSocket);

		virtual ~LobbyUser() = default;

		int64_t Id() const override;

		bool Initiailize();
		void ReadMessage(const uint8_t* pData, std::size_t dataSize) override;
	private:
		void HandleRead();
		void HandleWrite();

		void OnDisconnected() override;
		void OnAccepted() override;
	private:
		int64_t                  m_id;
		std::shared_ptr<ISocket> m_pSocket;
	};
}