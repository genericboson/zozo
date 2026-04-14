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
		CacheTxPtr NewTx();
		void RunAsync(const CacheTxPtr& tx);
		asio::awaitable<void> DestroyConsumed(CacheTx* tx);

		asio::awaitable<void> Consume(CacheTx* tx);
		asio::awaitable<void> ConsumeAll();
	private:
		lockfree::queue<CacheTx*, lockfree::capacity<128>, lockfree::fixed_sized<false>> m_txQueue;
		std::unordered_map<int32_t, std::shared_ptr<CacheTx>> m_txHolder;
	};
}