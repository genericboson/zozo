#pragma once

#include "../Types.h"
#include "CacheTxOption.h"

namespace GenericBoson
{
	class ICacheObject;
	enum class CacheTxState;
	class TxExecutor;

	class CacheTx : public std::enable_shared_from_this<CacheTx>
	{
		friend class WritableObject;
		friend class TxExecutor;

		template<typename CALLABLE>
		friend std::shared_ptr<CacheTx>& operator|(std::shared_ptr<CacheTx>& pTx, CALLABLE&& rhs);

		template<typename CALLABLE>
		friend CacheTx& operator|(CacheTx& pTx, CALLABLE&& rhs);

	public:
		CacheTx(TxExecutor& txExecutor);

		void ResetAll();
		CacheTx& RunAsync();

		TxExecutor& GetExecutor() { return m_executor; }

	public:
		template<typename OBJ>
		std::shared_ptr<OBJ> New()
		{
			auto newObj = std::make_shared<OBJ>(*this);
			m_objects.push_back(newObj);
			return newObj;
		}

	private:
		asio::awaitable<bool> RunOnUpdate();

	private:
		int64_t                                  m_id;
		CacheTxOption                            m_option;

		std::list<std::shared_ptr<ICacheObject>> m_objects;
		CacheTxState                             m_state;
												 
		std::list<CacheTxPostCallback>           m_postCallbacks;
		TxExecutor&                              m_executor;
	};

	using CacheTxPtr = std::shared_ptr<CacheTx>;
}