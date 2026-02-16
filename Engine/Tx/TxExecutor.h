#pragma once

#include <boost/lockfree/queue.hpp>

#include "CacheTx.h"
#include "Engine/Types.h"

namespace GenericBoson
{
	namespace lockfree = boost::lockfree;

	class TxExecutor
	{
	public:
		void Consume(const CacheTx* tx);
		void ConsumeAll();

	private:
		lockfree::queue<CacheTx*, lockfree::capacity<128>, lockfree::fixed_sized<false>> m_txQueue;
	};
}