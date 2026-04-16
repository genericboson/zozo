#pragma once

#include <boost/lockfree/queue.hpp>
#include <boost/mysql.hpp>

#include "MemObject.h"
#include "MemTx.h"
#include "Engine/Types.h"

namespace GenericBoson
{
	namespace lockfree = boost::lockfree;
	namespace asio = boost::asio;
	namespace mysql = boost::mysql;

	class TxExecutor
	{
		friend class WritableObject;
		friend class MemTx;

	public:
		MemTxPtr NewTx();
		void RunAsync(const MemTxPtr& tx);
		asio::awaitable<void> DestroyConsumed(MemTx* tx);

		asio::awaitable<void> Consume(MemTx* tx);
		asio::awaitable<void> ConsumeAll();
	private:
		lockfree::queue<MemTx*, lockfree::capacity<128>, lockfree::fixed_sized<false>> m_txQueue;
		std::unordered_map<int32_t, std::shared_ptr<MemTx>> m_txHolder;
	};
}