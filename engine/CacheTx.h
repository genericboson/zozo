#pragma once

#include <functional>
#include <list>
#include <memory>

#include "CacheObject.h"
#include "CacheTxOption.h"
#include "CacheTxState.h"
#include "TxExecutor.h"

namespace GenericBoson
{
	class CacheTx
	{
	public:
	private:
		int32_t                                       m_id;
		CacheTxOption                                 m_option;
		std::list< CacheObject >                      m_objects;
		CacheTxState                                  m_state;

		std::list< std::function< bool(void) > >      m_callbacks;
		std::weak_ptr< TxExecutor >                   m_wpExecutor;
	};
}