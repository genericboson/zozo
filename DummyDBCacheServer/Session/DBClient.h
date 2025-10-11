#pragma once

#include <Engine/Tx/TxExecutor.h>
#include <Engine/IActor.h>

namespace GenericBoson
{
	class ISocket;

	class DBClient :
		public IActor,
		public TxExecutor,
		public std::enable_shared_from_this<DBClient>
	{
	public:
		DBClient(const std::shared_ptr<ISocket>& pSocket);

		virtual ~DBClient() = default;

		int64_t Id() const override;

		bool Initialize() override;

		void Write();
		awaitable<void> Read(const uint8_t* pData, std::size_t dataSize) override;
	private:
		void OnDisconnected() override;
		void OnAccepted() override;
	private:
		int64_t                  m_id;
		std::shared_ptr<ISocket> m_pSocket;
	};
}