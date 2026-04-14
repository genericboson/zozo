#include "PCH.h"

#include "Engine/Tx/CacheTx.h"
#include "TxExecutor.h"

namespace GenericBoson
{
    CacheTxPtr TxExecutor::NewTx()
    {
        return std::make_shared<CacheTx>(*this);
    }

    asio::awaitable<void> TxExecutor::DestroyConsumed(CacheTx* tx)
    {
        NULL_CO_RETURN(m_txHolder.erase(tx->m_id));
		co_return;
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
            co_await DestroyConsumed(tx);
        }
    }
}
