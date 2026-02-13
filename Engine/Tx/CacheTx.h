#pragma once

#include "Types.h"
#include "CacheTxOption.h"

namespace GenericBoson
{
	class CacheObject;
	enum class CacheTxState;
	class TxExecutor;

	class CacheTx
	{
	public:
		bool RunTx(CacheTxCallback&& callback);
	public:
		static std::shared_ptr<CacheTx> Create();

	private:
		int32_t                               m_id;
		CacheTxOption                         m_option;
		std::list<std::weak_ptr<CacheObject>> m_objects;
		CacheTxState                          m_state;

		std::list< CacheTxCallback >          m_callbacks;
		std::weak_ptr< TxExecutor >           m_wpExecutor;
	};
}