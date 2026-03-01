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
		friend class CacheObject;

		template<typename CALLABLE>
		friend std::shared_ptr<CacheTx>& operator|(std::shared_ptr<CacheTx>& pTx, CALLABLE&& rhs);

		template<typename CALLABLE>
		friend CacheTx& operator|(CacheTx& pTx, CALLABLE&& rhs);

	public:
		CacheTx(TxExecutor& txExecutor);

		void ResetAll();
		asio::awaitable<bool> RunTx();

	public:
		template<typename OBJ>
		std::shared_ptr<OBJ> New()
		{
			auto newObj = std::make_shared<OBJ>(*this);
			return newObj;
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