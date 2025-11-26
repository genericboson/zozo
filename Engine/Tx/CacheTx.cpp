#include "PCH.h"

#include "CacheTx.h"

#include "CacheObject.h"
#include "CacheTxOption.h"
#include "CacheTxState.h"
#include "TxExecutor.h"

namespace GenericBoson
{
	std::shared_ptr<CacheTx> CacheTx::Create()
	{
		return std::make_shared<CacheTx>();
	}
}