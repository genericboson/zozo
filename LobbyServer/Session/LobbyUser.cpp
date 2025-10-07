#include "PCH.h"

#include <memory>

#include <boost/asio.hpp>

#include <flatbuffers/flatbuffers.h>

#include <Engine/Socket/ISocket.h>
#include <Engine/Socket/BoostTcpSocket.h>

#include <MessageSchema/External/LobbyServer_generated.h>
#include <MessageSchema/Internal/DBCacheLobby_generated.h>

#include <DBCacheClient/DBCacheClient.h>

#include "LobbyUser.h"

namespace GenericBoson
{
    LobbyUser::LobbyUser(const std::shared_ptr<ISocket>& pSocket)
        : m_id(0), m_pSocket(pSocket)
    {
    }

    int64_t LobbyUser::Id() const
    {
        return m_id;
    }

    bool LobbyUser::Initiailize()
    {
        if (!m_pSocket->IsValid())
            return false;

        HandleRead();
    }

    void LobbyUser::HandleRead()
    {
        m_pSocket->ReadHeader();
    }

    void LobbyUser::HandleWrite()
    {
    }

    void LobbyUser::OnDisconnected()
    {
    }

    void LobbyUser::ReadMessage(const uint8_t* pData, std::size_t dataSize)
    {
        using namespace Zozo;

        auto verifier = flatbuffers::Verifier(pData, dataSize);
        if (!VerifyLobbyMessageBuffer(verifier))
            return;

        auto message = Zozo::GetLobbyMessage(pData);
        NULL_RETURN(message)

        switch (message->payload_type())
        {
        case LobbyPayload::LobbyPayload_LoginReq:
            {
			    auto loginReq = message->payload_as_LoginReq();
                NULL_RETURN(loginReq);

                /*DBCacheClient::GetInstance()->Upsert(loginReq) |
                    [](const DBCacheLobbyMessage& ack)
                    {

                    };*/
            }
            break;
        case LobbyPayload::LobbyPayload_LoginAck:
            {
                ERROR_LOG("Logic error");
            }
            break;
        default:
                WARN_LOG("Unhandled message ( payload_type - %s )",
                    EnumNameLobbyPayload(message->payload_type()));
                break;
            }
    }
}
