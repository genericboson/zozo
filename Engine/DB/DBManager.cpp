#include "PCH.h"

#include <boost/exception/diagnostic_information.hpp>

#include "DBManager.h"
#include "EnvironmentVariable.h"

namespace GenericBoson
{
	bool DBManager::Initialize(asio::io_context& ctx)
	{
		try
		{
			m_pDbPool = std::make_unique<mysql::connection_pool>(ctx,
				GetDbPoolParams(
					Environment::GetDBHost(),
					Environment::GetDBPort(),
					Environment::GetDBUser(),
					Environment::GetDBPassword(),
					Environment::GetDBName()
				)
			);
		}
		catch (const boost::exception& ex)
		{
			WARN_LOG("Failed to initialize DB connection pool. error info : {}", 
				boost::diagnostic_information(ex));
			return false;
		}
		return true;
	}

	mysql::pool_params DBManager::GetDbPoolParams(
		std::string_view hostname,
		uint16_t         port,
		std::string_view username,
		std::string_view password,
		std::string_view dbname)
	{
		mysql::pool_params params;
		params.server_address.emplace_host_and_port(hostname.data());
		params.username = username;
		params.password = password;
		params.database = dbname;
		//params.thread_safe = true;

		return params;
	}
}