#pragma once

#include <boost/mysql.hpp>

#include "Engine/Singleton.h"

namespace GenericBoson
{
	namespace mysql = boost::mysql;
	namespace asio  = boost::asio;

	class DBManager : public Singleton<DBManager>
	{
	public:
		DBManager() = default;
		virtual ~DBManager() = default;

		bool Initialize(asio::io_context& ctx);

	private:
		static mysql::pool_params GetDbPoolParams(
			std::string_view hostname,
			uint16_t         port,
			std::string_view username,
			std::string_view password,
			std::string_view dbname);

	private:
		std::unique_ptr<mysql::connection_pool> m_pDbPool;

		uint16_t                                m_dbPort;
	};
}