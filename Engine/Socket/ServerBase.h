#pragma once

#include <boost/asio.hpp>

namespace GenericBoson
{
	class IActor;
	class ISocket;
	
	class ServerBase
	{
	public:
		ServerBase(int32_t port);
		virtual ~ServerBase() = default;

		bool Start();
		void Stop();

		void HandleAccept();

		virtual auto CreateActor(const std::shared_ptr<ISocket>& pSocket)
			-> std::shared_ptr<IActor> = 0;

	private:
		boost::asio::io_context             m_ioContext;
		boost::asio::ip::tcp::acceptor      m_acceptor;

		boost::asio::executor_work_guard<
			boost::asio::io_context::executor_type>
			m_workGuard;
	};
}