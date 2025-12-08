#pragma once

#include <boost/asio.hpp>

#include <Engine/Socket/InternalClient.h>
#include <Engine/Socket/ServerBase.h>

#include "Actor/LobbyProxy.h"
#include "Actor/Zone.h"

namespace GenericBoson
{
	class GameServer : 
		public ServerBase, 
		public std::enable_shared_from_this<GameServer>
	{
		friend class LobbyProxy;
		friend class Character;

	public:
		GameServer(int32_t port);

		virtual ~GameServer() = default;

		bool Start() override;
		bool AfterReadIni() override;
		auto CreateActor(const std::shared_ptr<ISocket>& pSocket) 
			-> std::shared_ptr<IActor> override;

	public:
		static auto CreateGameServer(int32_t port = 8001) -> std::shared_ptr<GameServer>;

	private:
		void InitializeSingletons();

	protected:
		std::optional<pt::ptree> ReadIni() override;

	private:
		std::unordered_map< int64_t, Zone > m_zones;

		std::unique_ptr<InternalClient>     m_pClient;
										    
		std::shared_ptr<IActor>             m_pLobbyProxy;

		std::string                         m_lobbyIp, m_lobbyPort;

		int32_t                             m_id;
	};
}