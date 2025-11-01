#pragma once

#include <Engine/Tx/TxExecutor.h>
#include <Engine/IActor.h>

namespace GenericBoson
{
	class ISocket;
	class Zone;

	namespace asio  = boost::asio;
	namespace mysql = boost::mysql;

	class Character : 
		public IActor, 
		public TxExecutor,
		public std::enable_shared_from_this<Character>
	{
	public:
		Character(const std::shared_ptr<ISocket>& pSocket );

		virtual ~Character() = default;

		int64_t Id() const override;

		bool Initialize() override;

		void Write();
		asio::awaitable<void> Read(const uint8_t* pData, std::size_t dataSize) override;
	private:
		void OnDisconnected() override;
		void OnAccepted() override;
	private:
		int64_t                  m_id;
		std::shared_ptr<ISocket> m_pSocket;
		std::weak_ptr<Zone>      m_wpZone;
	};
}