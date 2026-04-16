#include "PCH.h"

#include "MemTx.h"

#include "MemObject.h"
#include "Numeric/IdGenerator.h"
#include "TxExecutor.h"

namespace GenericBoson
{
	MemTx::MemTx(TxExecutor& txExecutor)
		: m_executor(txExecutor)
	{
	}

	void MemTx::ResetAll()
	{
		m_objects.clear();
		m_postCallbacks.clear();
	}

	asio::awaitable<bool> MemTx::RunOnUpdate()
	{
		DBResult dbResult{ .resultCode = Zozo::ResultCode::ResultCode_Success };
		for (const auto& obj : m_objects)
		{
			if (!co_await obj->Execute(dbResult))
			{
				WARN_LOG("Failed to execute mem object. object name - {}", 
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

	MemTx& MemTx::RunAsync()
	{
		m_executor.m_txHolder.emplace(m_id, shared_from_this());
		m_executor.m_txQueue.push(this);
		return *this;
	}
}