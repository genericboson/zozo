#pragma once

namespace GenericBoson
{
	class GameServer
	{
	public:
		GameServer(int32_t port = 8001);
		virtual ~GameServer() = default;

		bool Start();
		void Stop();
	};
}