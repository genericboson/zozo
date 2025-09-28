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

		boost::asio::executor_work_guard<
			boost::asio::io_context::executor_type>
				                            m_workGuard;

		std::unordered_map< int64_t, Zone > m_zones;
	};
}