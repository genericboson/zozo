#include "PCH.h"

#include "CacheTx.h"
#include "TxExecutor.h"

namespace GenericBoson
{
    TxExecutor::TxExecutor(mysql::any_connection& dbConn)
		: m_dbConn(dbConn)
    {
    }

    void TxExecutor::Consume(CacheTx* tx)
    {
        NULL_RETURN(tx);
        tx->RunOnUpdate();
    }

    void TxExecutor::ConsumeAll()
    {
        CacheTx* tx;
        while (m_txQueue.pop(tx))
        {
            Consume(tx);
        }
    }
}
