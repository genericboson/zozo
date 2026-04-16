#pragma once

#define BOOST_THREAD_PROVIDES_FUTURE
#define BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION

#include <memory>

#include <boost/thread/future.hpp>

#include "MemTx.h"
#include "Engine/Concepts.h"

namespace GenericBoson
{
	template<typename CALLABLE>
	MemTx& operator|(MemTx& tx, CALLABLE&& rhs)
	{
		//static_assert(MemTxPostCallbackLike<CALLABLE>);
		tx.m_postCallbacks.emplace_back(std::forward<CALLABLE>(rhs));
		return tx;
	}

	template<typename CALLABLE>
	std::shared_ptr<MemTx>& operator|(std::shared_ptr<MemTx>& pTx, CALLABLE&& rhs)
	{
		//static_assert(MemTxPostCallbackLike<CALLABLE>);
		pTx->m_postCallbacks.emplace_back(std::forward<CALLABLE>(rhs));
		return pTx;
	}
}