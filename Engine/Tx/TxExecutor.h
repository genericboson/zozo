#pragma once

#include <boost/lockfree/queue.hpp>
#include <boost/mysql.hpp>

#include "CacheObject.h"
#include "CacheTx.h"
#include "Engine/Types.h"

namespace GenericBoson
{
	namespace lockfree = boost::lockfree;
	namespace asio = boost::asio;
	namespace mysql = boost::mysql;

	class TxExecutor
	{
		friend class WritableObject;
		friend class CacheTx;

	public:
		TxExecutor(mysql::any_connection& dbConn);

		CacheTxPtr NewTx();
		asio::awaitable<void> DestroyConsumed(CacheTx* tx);

		asio::awaitable<void> Consume(CacheTx* tx);
		asio::awaitable<void> ConsumeAll();

		mysql::any_connection& GetDbConnection() { return m_dbConn; }

	private:
		mysql::any_connection&    m_dbConn;

		lockfree::queue<CacheTx*, lockfree::capacity<128>, lockfree::fixed_sized<false>> m_txQueue;
		std::unordered_map<int32_t, std::shared_ptr<CacheTx>> m_txHolder;
	};
}