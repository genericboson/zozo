#pragma once

#include <Engine/Tx/TxExecutor.h>
#include <Engine/IActor.h>

#include <MessageSchema/Common/Type_generated.h>
#include <MessageSchema/Common/CharacterInfo_generated.h>

namespace GenericBoson
{
	class GameServer;
	class ISocket;
	class Zone;

	namespace asio  = boost::asio;

	class Character : 
		public IActor, 
		public TxExecutor,
		public std::enable_shared_from_this<Character>
	{
	public:
		Character(
			const std::shared_ptr<GameServer>& pServer, 
			const std::shared_ptr<ISocket>&    pSocket);

		virtual ~Character() = default;

		int64_t Id() const override;

		bool Initialize() override;

		void Write(const uint8_t* pData, const std::size_t size);
		asio::awaitable<void> Read(const uint8_t* pData, std::size_t dataSize) override;
	private:
		void OnDisconnected() override;
		void OnAccepted() override;
	private:
		int64_t                   m_id;
		std::string               m_token;

		Zozo::CharacterInfoT 	  m_info;
		Zozo::Vector2I            m_position;

		std::shared_ptr<ISocket>  m_pSocket;
		std::weak_ptr<Zone>       m_wpZone;

		std::weak_ptr<GameServer> m_wpServer;
	};
}