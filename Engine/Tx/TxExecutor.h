#pragma once

//#include <boost/asio.hpp>

#include "Engine/Types.h"

namespace GenericBoson
{
	class CacheTx;
	enum class EResultCode;

	class TxExecutor
	{
	public:
		EResultCode RunTx(const CacheTx& tx, CacheTxCallback&& callback);

	private:
		//boost::asio::execution_context* context;
	};
}