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

	asio::awaitable<bool> CacheTx::RunTx()
	{
		for (const auto& callback : m_preCallbacks)
		{
			if (!co_await callback())
				co_return false;
		}

		DBResult result{ .resultCode = Zozo::ResultCode::ResultCode_Success };
		{
			for (const auto& obj : m_objects)
			{
				obj->Execute();
			}
		}

		for (const auto& callback : m_postCallbacks)
		{
			if (!co_await callback(result))
				co_return false;
		}

		co_return true;
	}
}