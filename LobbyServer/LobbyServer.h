#pragma once

#include <boost/asio.hpp>

namespace GenericBoson
{
	class LobbyServer
	{
	public:
		LobbyServer(int32_t port = 8002);
		virtual ~LobbyServer() = default;

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
	};
}