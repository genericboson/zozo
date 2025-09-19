#pragma once

#include <functional>
#include <list>
#include <memory>

#include "Types.h"
#include "CacheTxOption.h"

namespace GenericBoson
{
	class CacheObject;
	enum class CacheTxState;
	class TxExecutor;

	class CacheTx
	{
	public:
	private:
		int32_t                      m_id;
		CacheTxOption                m_option;
		std::list< CacheObject >     m_objects;
		CacheTxState                 m_state;

		std::list< CacheTxCallback > m_callbacks;
		std::weak_ptr< TxExecutor >  m_wpExecutor;
	};
}