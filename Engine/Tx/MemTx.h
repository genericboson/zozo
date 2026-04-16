#pragma once

#include "../Types.h"
#include "MemTxOption.h"

namespace GenericBoson
{
	class IMemObject;
	enum class MemTxState;
	class TxExecutor;

	class MemTx : public std::enable_shared_from_this<MemTx>
	{
		friend class WritableObject;
		friend class TxExecutor;

		template<typename CALLABLE>
		friend std::shared_ptr<MemTx>& operator|(std::shared_ptr<MemTx>& pTx, CALLABLE&& rhs);

		template<typename CALLABLE>
		friend MemTx& operator|(MemTx& pTx, CALLABLE&& rhs);

	public:
		MemTx(TxExecutor& txExecutor);

		void ResetAll();
		MemTx& RunAsync();

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
		MemTxOption                            m_option;

		std::list<std::shared_ptr<IMemObject>> m_objects;
		MemTxState                             m_state;
												 
		std::list<MemTxPostCallback>           m_postCallbacks;
		TxExecutor&                              m_executor;
	};

	using MemTxPtr = std::shared_ptr<MemTx>;
}