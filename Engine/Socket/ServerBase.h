#pragma once

#include <boost/asio.hpp>
#include <boost/asio/use_awaitable.hpp>

namespace GenericBoson
{
	class IActor;
	class ISocket;

	using namespace boost::asio;

	class ServerBase
	{
	public:
		ServerBase(int32_t port);
		virtual ~ServerBase() = default;

		bool            Start();
		void            Stop();

		void            Accept();
		awaitable<void> Listen();
		awaitable<void> Read(ip::tcp::socket&& socket);

		virtual auto CreateActor(const std::shared_ptr<ISocket>& pSocket)
			-> std::shared_ptr<IActor> = 0;

	private:
		std::atomic_bool                               m_isRunning{ true };

		io_context                                     m_ioContext;
		ip::tcp::acceptor                              m_acceptor;

		executor_work_guard<io_context::executor_type> m_workGuard;
	};
}