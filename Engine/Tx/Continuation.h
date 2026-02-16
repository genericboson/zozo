#pragma once

#define BOOST_THREAD_PROVIDES_FUTURE
#define BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION

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
}