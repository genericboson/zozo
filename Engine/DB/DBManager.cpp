#include "PCH.h"

#include <boost/asio.hpp>
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

		m_pDbPool->async_run(asio::detached);

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
		params.username      = username;
		params.password      = password;
		params.database      = dbname;
		params.thread_safe   = true;
		params.multi_queries = true;

		return params;
	}

	auto DBManager::GetConnection()
		-> asio::awaitable<std::optional<mysql::pooled_connection>>
	{
		auto trialCount = Environment::GetGetConnTrialCount();
		while(trialCount--)
		{
			auto [err, conn] = co_await m_pDbPool->async_get_connection(
				asio::as_tuple(asio::cancel_after(std::chrono::microseconds(Environment::GetGetConnTimeoutMs()))));

			if (err == boost::system::errc::success)
				co_return std::move(conn);

			WARN_LOG("Failed to get DB connection. error code - {}({})",
				err.value(), err.message());
		}

		WARN_LOG("Try getting DB connection timed out. trial coiunt - {}",
			Environment::GetGetConnTrialCount());

		co_return std::nullopt;
	}
}