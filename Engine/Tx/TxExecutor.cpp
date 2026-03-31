#include "PCH.h"

#include "Engine/Tx/CacheTx.h"
#include "Numeric/IdGenerator.h"
#include "TxExecutor.h"

namespace GenericBoson
{
    TxExecutor::TxExecutor(mysql::any_connection& dbConn)
		: m_dbConn(dbConn)
    {
    }

    CacheTxPtr TxExecutor::NewTx()
    {
		auto newTx = std::make_shared<CacheTx>(*this);
        m_txHolder.emplace(IdGenerator::CreateId(0), newTx);

        if (!m_txQueue.push(newTx.get()))
        {
            WARN_LOG("Failed to push CacheTx to TxExecutor's queue. CacheTx will not be executed.");
        }

        return newTx;
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
            DestroyConsumed(tx);
        }
    }
}
