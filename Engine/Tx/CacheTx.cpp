#include "PCH.h"

#include "CacheTx.h"

#include "CacheObject.h"
#include "CacheTxOption.h"
#include "CacheTxState.h"
#include "TxExecutor.h"

namespace GenericBoson
{
	CacheTx::CacheTx(TxExecutor& txExecutor)
		: m_executor(txExecutor)
	{
	}

	void CacheTx::ResetAll()
	{
		m_objects.clear();
		m_preCallbacks.clear();
		m_postCallbacks.clear();
	}

	asio::awaitable<bool> CacheTx::RunOnUpdate()
	{
		DBResult result{ .resultCode = Zozo::ResultCode::ResultCode_Success };
		{
			for (const auto& obj : m_objects)
			{
				if (!co_await obj->Execute())
					co_return false;
			}
		}

		for (const auto& callback : m_postCallbacks)
		{
			if (!co_await callback(result))
				co_return false;
		}

		ResetAll();

		co_return true;
	}

	asio::awaitable<bool> CacheTx::RunTx()
	{
		// #todo : push to TxExecutor's lock free queue

		co_return true;
	}
}