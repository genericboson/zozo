#pragma once

#include <boost/asio.hpp>
#include <boost/asio/thread_pool.hpp>
#include <boost/asio/use_awaitable.hpp>

#include <boost/mysql.hpp>

namespace GenericBoson
{
	class IActor;
	class ISocket;

	namespace asio = boost::asio;
	namespace mysql = boost::mysql;

	class ServerBase
	{
	public:
		ServerBase(int32_t port);
		virtual ~ServerBase() = default;

		bool            Start();
		void            Stop();

		void            Accept();
		awaitable<void> Listen();

		bool            IsRunning() const;

		virtual auto CreateActor(const std::shared_ptr<ISocket>& pSocket)
			-> std::shared_ptr<IActor> = 0;

	private:
		static mysql::pool_params GetDbParams(
			std::string_view hostname,
			std::string_view username,
			std::string_view password,
			std::string_view dbname);

	public:
		mysql::connection_pool                                     m_dbConnPool;

	private:
		std::atomic_bool                                           m_isRunning{ true };

		asio::io_context                                           m_acceptIoContext;
		asio::thread_pool                                          m_networkThreadPool{ std::thread::hardware_concurrency() * 2 };
		asio::strand<asio::thread_pool::executor_type>             m_strand{ make_strand(m_networkThreadPool.get_executor()) };
		ip::tcp::acceptor                                          m_acceptor;
		asio::executor_work_guard<asio::io_context::executor_type> m_workGuard;

		asio::thread_pool                                          m_dbThreadPool{ std::thread::hardware_concurrency() * 2 };
	};
}