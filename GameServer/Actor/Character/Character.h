#pragma once

#include <Engine/Tx/TxExecutor.h>
#include <Engine/IActor.h>

namespace GenericBoson
{
	class ISocket;
	class Zone;

	class Character : 
		public IActor, 
		public TxExecutor,
		public std::enable_shared_from_this<Character>
	{
	public:
		Character(const std::shared_ptr<ISocket>& pSocket );

		virtual ~Character() = default;

		int64_t Id() const override;

		bool Initiailize();
		void ReadMessage(const uint32_t id, const uint8_t* pData, std::size_t dataSize) override;
	private:
		void HandleRead();
		void HandleWrite();

		void OnDisconnected() override;
	private:
		int64_t                    m_id;
		std::shared_ptr<ISocket> m_pSocket;
		std::weak_ptr<Zone>      m_wpZone;
	};
}