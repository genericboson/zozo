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
		CacheTx(TxExecutor& txExecutor);

		asio::awaitable<bool> RunTx();

		template<typename OBJ>
		std::shared_ptr<OBJ> New()
		{
			auto newObj = std::make_shared<OBJ>(*this);
			return
		}

	private:
		int32_t                                 m_id;
		CacheTxOption                           m_option;
		std::list<std::shared_ptr<CacheObject>> m_objects;
		CacheTxState                            m_state;

		std::list< CacheTxPreCallback >         m_preCallbacks;
		std::list< CacheTxPostCallback >        m_postCallbacks;
		TxExecutor&                             m_executor;
	};
}