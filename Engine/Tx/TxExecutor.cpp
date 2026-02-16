#include "PCH.h"

#include "CacheTx.h"
#include "TxExecutor.h"

namespace GenericBoson
{
    void TxExecutor::Consume(const CacheTx* tx)
    {
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
