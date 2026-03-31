#include "PCH.h"

#include "CacheTx.h"
#include "TxExecutor.h"

namespace GenericBoson
{
    TxExecutor::TxExecutor(mysql::any_connection& dbConn)
		: m_dbConn(dbConn)
    {
    }

    asio::awaitable<void> TxExecutor::Consume(CacheTx* tx)
    {
        NULL_CO_RETURN(tx);
        co_await tx->RunOnUpdate();
    }

    asio::awaitable<void> TxExecutor::ConsumeAll()
    {
        CacheTx* tx = nullptr;
        while (m_txQueue.pop(tx))
        {
            co_await Consume(tx);
        }
    }
}
