#include "PCH.h"

#include "Engine/Tx/MemTx.h"
#include "TxExecutor.h"

namespace GenericBoson
{
    MemTxPtr TxExecutor::NewTx()
    {
        return std::make_shared<MemTx>(*this);
    }

    asio::awaitable<void> TxExecutor::DestroyConsumed(MemTx* tx)
    {
        NULL_CO_RETURN(m_txHolder.erase(tx->m_id));
		co_return;
    }

    asio::awaitable<void> TxExecutor::Consume(MemTx* tx)
    {
        NULL_CO_RETURN(tx);
        co_await tx->RunOnUpdate();
    }

    asio::awaitable<void> TxExecutor::ConsumeAll()
    {
        MemTx* tx = nullptr;
        while (m_txQueue.pop(tx))
        {
            co_await Consume(tx);
            co_await DestroyConsumed(tx);
        }
    }
}
