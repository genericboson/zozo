#pragma once

#include <boost/asio.hpp>

#include <Engine/Socket/ServerBase.h>

#include "Actor/Zone.h"

namespace GenericBoson
{
	class GameServer : public ServerBase
	{
	public:
		GameServer(int32_t port = 8001);
		virtual ~GameServer() = default;

		auto CreateActor(const std::shared_ptr<ISocket>& pSocket) 
			-> std::shared_ptr<IActor> override;
	private:
		std::unordered_map< int64_t, Zone > m_zones;
	};
}