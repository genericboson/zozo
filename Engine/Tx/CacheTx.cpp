#include "PCH.h"

#include "CacheTx.h"

#include "CacheObject.h"
#include "Numeric/IdGenerator.h"
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
		m_postCallbacks.clear();
	}

	asio::awaitable<bool> CacheTx::RunOnUpdate()
	{
		DBResult dbResult{ .resultCode = Zozo::ResultCode::ResultCode_Success };
		for (const auto& obj : m_objects)
		{
			if (!co_await obj->Execute(dbResult))
			{
				WARN_LOG("Failed to execute cache object. object name - {}", 
					obj->GetObjectName());
				co_return false;
			}

		}

		for (const auto& callback : m_postCallbacks)
		{
			if (!co_await callback(dbResult))
			{
				WARN_LOG("Failed to call post callback. object name - {}");
				co_return false;
			}
		}

		ResetAll();

		co_return true;
	}

	CacheTx& CacheTx::RunAsync()
	{
		m_executor.m_txHolder.emplace(IdGenerator::CreateId(0), shared_from_this());
		m_executor.m_txQueue.push(this);
		return *this;
	}
}