#include "PCH.h"

#include <memory>

#include <boost/asio.hpp>

#include <flatbuffers/flatbuffers.h>

#include <Engine/Socket/ISocket.h>
#include <Engine/Socket/BoostTcpSocket.h>
#include <Engine/Tx/Continuation.h>

#include <MessageSchema/Internal/DBCache_generated.h>

#include <DBCacheClient/DBCacheClient.h>

#include "DBClient.h"
#include "DBClientManager.h"

namespace GenericBoson
{
    DBClient::DBClient(const std::shared_ptr<ISocket>& pSocket)
        : m_id(0), m_pSocket(pSocket)
    {
    }

    int64_t DBClient::Id() const
    {
        return m_id;
    }

    bool DBClient::Initialize()
    {
        if (!m_pSocket->IsValid())
            return false;

        DBClientManager::GetInstance()->AddDBClient(shared_from_this());
        return true;
    }

    void DBClient::Write()
    {
    }

    void DBClient::OnDisconnected()
    {
    }

    void DBClient::OnAccepted()
    {
        INFO_LOG("DBClient accepted ( DBClientId - {} )", m_id);
    }

    awaitable<void> DBClient::Read(const uint8_t* pData, std::size_t dataSize)
    {
        using namespace Zozo;

        auto verifier = flatbuffers::Verifier(pData, dataSize);
        if (!VerifyDBCacheMessageBuffer(verifier))
            return;

        auto message = Zozo::GetDBCacheMessage(pData);
        NULL_RETURN(message)

            switch (message->payload_type())
            {
            default:
                WARN_LOG("Unhandled message ( payload_type - %s )",
                    EnumNameDBCachePayload(message->payload_type()));
                break;
            }
    }

    //void LobbyUser::SendLoginAck()
    //{
    //    // for debug
    //    flatbuffers::FlatBufferBuilder fbb;
    //    auto gameserverIp = fbb.CreateString("127.0.0.1");
    //    auto gameserverPort = fbb.CreateString("8001");
    //    auto token = fbb.CreateString("TestTokenA");
    //    auto loginDBAck = Zozo::CreateLoginDBAck(
    //        fbb, Zozo::InternalResultCode_Success,
    //        gameserverIp, gameserverPort, token);
    //    auto lobbyMsg = Zozo::CreateDBCacheLobbyMessage(fbb,
    //        Zozo::DBCacheLobbyPayload_LoginDBAck, loginDBAck.Union());
    //    fbb.Finish(lobbyMsg);

    //    m_pSocket->EnqueueMessage(fbb.GetBufferPointer(), fbb.GetSize());
    //}
}
