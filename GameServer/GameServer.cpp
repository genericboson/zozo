#include "PCH.h"

#include <Engine/Socket/BoostTcpSocket.h>

#include "Actor/Character/Character.h"
#include "Actor/Character/CharacterManager.h"
#include "GameServer.h"

namespace GenericBoson
{
	GameServer::GameServer(int32_t port /*= 8001*/)
		: m_acceptor(
			m_ioContext, 
			boost::asio::ip::tcp::endpoint(
				boost::asio::ip::tcp::v4(), port))
	{

	}

	bool GameServer::Start()
	{
		HandleAccept();
		return true;
	}

	void GameServer::Stop()
	{
	}

	void GameServer::HandleAccept()
	{
		m_acceptor.async_accept(
			[this](const boost::system::error_code& error,
				boost::asio::ip::tcp::socket socket)
			{
				if (!error)
				{
					auto pCharacter = std::make_shared<Character>(
						std::make_shared<BoostTcpSocket>(std::move(socket)));
					INFO_LOG( "Clientd accepted ( ClientId - %lld", pCharacter->Id() );

					CharacterManager::GetInstance()->AddCharacter(std::move(pCharacter));
				}
			});
	}
}