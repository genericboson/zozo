#pragma once

#include "../Types.h"
#include "CacheTxOption.h"

namespace GenericBoson
{
	class CacheObject;
	enum class CacheTxState;
	class TxExecutor;

	class CacheTx
	{
	public:
		asio::awaitable<bool> RunTx();
	public:
		static std::shared_ptr<CacheTx> Create();

	private:
		int32_t                                 m_id;
		CacheTxOption                           m_option;
		std::list<std::shared_ptr<CacheObject>> m_objects;
		CacheTxState                            m_state;

		std::list< CacheTxPreCallback >         m_preCallbacks;
		std::list< CacheTxPostCallback >        m_postCallbacks;
		TxExecutor*                             m_pExecutor = nullptr;
	};
}