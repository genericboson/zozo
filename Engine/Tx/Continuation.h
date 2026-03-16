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
		//static_assert(CacheTxPostCallbackLike<CALLABLE>);
		tx.m_postCallbacks.emplace_back(std::forward<CALLABLE>(rhs));
		return tx;
	}

	template<typename CALLABLE>
	std::shared_ptr<CacheTx>& operator|(std::shared_ptr<CacheTx>& pTx, CALLABLE&& rhs)
	{
		//static_assert(CacheTxPostCallbackLike<CALLABLE>);
		pTx->m_postCallbacks.emplace_back(std::forward<CALLABLE>(rhs));
		return pTx;
	}
}