#pragma once

#include <boost/asio.hpp>

#include "Actor/Zone.h"

namespace GenericBoson
{
	class GameServer
	{
	public:
		GameServer(int32_t port = 8001);
		virtual ~GameServer() = default;

		bool Start();
		void Stop();

	private:
		void HandleAccept();

	private:
		boost::asio::io_context             m_ioContext;
		boost::asio::ip::tcp::acceptor      m_acceptor;

		std::unordered_map< int64_t, Zone > m_zones;
	};
}