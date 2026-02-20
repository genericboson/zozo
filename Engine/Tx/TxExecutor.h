#pragma once

#include <boost/lockfree/queue.hpp>
#include <boost/mysql.hpp>

#include "CacheTx.h"
#include "Engine/Types.h"

namespace GenericBoson
{
	namespace lockfree = boost::lockfree;
	namespace mysql = boost::mysql;

	class TxExecutor
	{
		friend class CacheObject;

	public:
		TxExecutor(mysql::any_connection& dbConn);

		void Consume(const CacheTx* tx);
		void ConsumeAll();

	private:
		mysql::any_connection&    m_dbConn;

		lockfree::queue<CacheTx*, lockfree::capacity<128>, lockfree::fixed_sized<false>> m_txQueue;
	};
}