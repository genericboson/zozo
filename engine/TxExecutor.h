#pragma once

#include <memory>

#include "Types.h"

namespace GenericBoson
{
	class CacheTx;
	enum class EResultCode;

	class TxExecutor : public std::enable_shared_from_this< TxExecutor >
	{
	public:
		EResultCode RunTx(const CacheTx& tx, CacheTxCallback&& callback);
	};
}