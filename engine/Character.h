#pragma once

#include "TxExecutor.h"

namespace GenericBoson
{
	class Character : public TxExecutor
	{
	public:
		int64_t Id() const;
	private:
		int64_t m_id;
	};
}