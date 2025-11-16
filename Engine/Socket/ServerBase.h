#pragma once

#include <boost/asio.hpp>
#include <boost/asio/thread_pool.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include <boost/mysql.hpp>

namespace GenericBoson
{
	class IActor;
	class ISocket;

	namespace asio = boost::asio;
	namespace mysql = boost::mysql;
	namespace pt = boost::property_tree;

	class ServerBase
	{
		friend class LobbyProxy;

	public:
		ServerBase(int32_t port);
		virtual ~ServerBase() = default;

		virtual bool Start();
		virtual bool AfterReadIni();
		virtual auto CreateActor(const std::shared_ptr<ISocket>& pSocket)
			-> std::shared_ptr<IActor> = 0;

		void Stop();

		void Accept();
		auto Listen()
			-> asio::awaitable<void>;

		bool IsRunning() const;

		asio::io_context& GetIoContextRef();

	protected:
		virtual std::optional<pt::ptree> ReadIni();

		bool InitializeConnection();

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
		std::unique_ptr<mysql::any_connection>                     m_pDbConn;

	protected:
		std::atomic_bool                                           m_isRunning{ true };

		int32_t                                                    m_listeningPort = 0;

		std::string                                                m_dbIp, 
		                                                           m_dbAccount, 
		                                                           m_dbPassword, 
		                                                           m_dbMainSchema;
		uint16_t                                                   m_dbPort;

		std::string                                                m_name;

		std::unique_ptr<std::jthread>                              m_pIoThread;
		std::unique_ptr<asio::ip::tcp::acceptor>                   m_pAcceptor;

		asio::io_context                                           m_ioContext;
		asio::thread_pool                                          m_networkThreadPool;
		asio::strand<asio::thread_pool::executor_type>             m_strand;
		asio::executor_work_guard<asio::io_context::executor_type> m_workGuard;
	};
}