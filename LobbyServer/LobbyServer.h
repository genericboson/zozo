#pragma once

#include <boost/asio.hpp>

#include <Engine/Socket/ServerBase.h>

namespace GenericBoson
{
	class LobbyServer : public ServerBase
	{
	public:
		enum class ELobbyServerSort : uint8_t
		{
			NONE = 0,
			EXTERNAL = 1,
			INTERNAL = 2,

			MAX
		};

	public:
		LobbyServer(ELobbyServerSort sort, int32_t port = 0);
		virtual ~LobbyServer() = default;

		auto CreateActor(const std::shared_ptr<ISocket>& pSocket)
			-> std::shared_ptr<IActor> override;

		bool Start() override;

		std::optional<pt::ptree> ReadIni() override;

	private:
		ELobbyServerSort m_sort = ELobbyServerSort::NONE;
	};
}