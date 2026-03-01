#pragma once

#define BOOST_THREAD_PROVIDES_FUTURE
#define BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION

#include <memory>

#include <boost/thread/future.hpp>

#include "CacheTx.h"
#include "Engine/Concepts.h"

namespace GenericBoson
{
	template<typename CALLABLE>
	CacheTx& operator|(CacheTx& tx, CALLABLE&& rhs)
	{
		if constexpr (CacheTxPostCallbackLike<CALLABLE>)
		{
			tx.m_postCallbacks.emplace_back(std::forward<CALLABLE>(rhs));
		}
		else
		{
			//std::assert(tx.m_postCallbacks.empty());
			tx.m_preCallbacks.emplace_back(std::forward<CALLABLE>(rhs));
		}

		return tx;
	}

	template<typename CALLABLE>
	std::shared_ptr<CacheTx>& operator|(std::shared_ptr<CacheTx>& pTx, CALLABLE&& rhs)
	{
		if constexpr (CacheTxPostCallbackLike<CALLABLE>)
		{
			pTx->m_postCallbacks.emplace_back(std::forward<CALLABLE>(rhs));
		}
		else
		{
			//std::assert(tx.m_postCallbacks.empty());
			pTx->m_preCallbacks.emplace_back(std::forward<CALLABLE>(rhs));
		}

		return pTx;
	}
}