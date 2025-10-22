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

		bool                  Start();
		void                  Stop();
						      
		void                  Accept();
		asio::awaitable<void> Listen();

		bool            IsRunning() const;

		virtual auto CreateActor(const std::shared_ptr<ISocket>& pSocket)
			-> std::shared_ptr<IActor> = 0;

	private:
		static mysql::pool_params GetDbPoolParams(
			std::string_view hostname,
			uint16_t         port,
			std::string_view username,
			std::string_view password,
			std::string_view dbname);

		static mysql::connect_params GetDbParams(
			std::string_view hostname,
			uint16_t         port,
			std::string_view username,
			std::string_view password,
			std::string_view dbname);

	public:
		//std::unique_ptr<mysql::connection_pool>                    m_pDbConnPool;
		std::unique_ptr<mysql::any_connection>                     m_pDbConn;

	private:
		std::atomic_bool                                           m_isRunning{ true };

		std::unique_ptr<std::jthread>                              m_pIoThread;

		asio::io_context                                           m_acceptIoContext;
		asio::io_context                                           m_dbIoContext;
		asio::thread_pool                                          m_networkThreadPool;
		//asio::thread_pool                                          m_dbThreadPool;
		asio::strand<asio::thread_pool::executor_type>             m_strand;
		asio::ip::tcp::acceptor                                    m_acceptor;
		asio::executor_work_guard<asio::io_context::executor_type> m_workGuard;
	};
}