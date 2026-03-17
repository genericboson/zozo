#pragma once

#include "../Types.h"
#include "CacheObject.h"
#include "CacheTxOption.h"

namespace GenericBoson
{
	class CacheObject;
	enum class CacheTxState;
	class TxExecutor;

	class CacheTx
	{
		template<typename T>
		friend class ReadableObject;
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

	public:
		template<typename OBJ>
		std::shared_ptr<OBJ> NewRead()
		{
			auto newObj = std::make_shared<OBJ>(*this);
			m_objects.emplace_back(std::move(newObj));
			return newObj;
		}

		template<typename OBJ>
		std::shared_ptr<OBJ> NewWrite()
		{
			auto newObj = std::make_shared<OBJ>(*this);
			m_objects.push_back(newObj);
			return newObj;
		}

	private:
		asio::awaitable<bool> RunOnUpdate();

	private:
		int32_t                                 m_id;
		CacheTxOption                           m_option;
		std::list<std::shared_ptr<CacheObject>> m_objects;
		CacheTxState                            m_state;

		std::list< CacheTxPostCallback >        m_postCallbacks;
		TxExecutor&                             m_executor;
	};
}