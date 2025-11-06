#pragma once

#include <boost/asio.hpp>

#include <Engine/Socket/ServerBase.h>

namespace GenericBoson
{
	class LobbyServer : public ServerBase
	{
	public:
		LobbyServer(int32_t port = 8002);
		virtual ~LobbyServer() = default;

		auto CreateActor(const std::shared_ptr<ISocket>& pSocket)
			-> std::shared_ptr<IActor> override;

		bool Start() override;
	};
}