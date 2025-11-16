#include "PCH.h"

#include <memory>

#include <boost/asio.hpp>
#include <boost/mysql.hpp>
#include <boost/mysql/static_results.hpp>
#include <boost/mysql/pfr.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <flatbuffers/flatbuffers.h>

#include <Engine/Socket/ISocket.h>
#include <Engine/Socket/BoostTcpSocket.h>
#include <Engine/Tx/Continuation.h>

#include "CharacterInfo_generated.h"
#include <MessageSchema/Internal/LobbyGame_generated.h>

#include "LobbyServer.h"
#include "LobbyStub.h"
#include "LobbyStubManager.h"
#include "StaticResults.h"

namespace GenericBoson
{
    LobbyStub::LobbyStub(
        LobbyServer& lobbyServer,
        const std::shared_ptr<ISocket>& pSocket)
        : m_id(0), m_server(lobbyServer), m_pSocket(pSocket)
    {
    }

    int64_t LobbyStub::Id() const
    {
        return m_id;
    }

    bool LobbyStub::Initialize()
    {
        if (!m_pSocket->IsValid())
            return false;

        LobbyStubManager::GetInstance()->AddLobbyStub(shared_from_this());
        return true;
    }

    void LobbyStub::Write()
    {
    }

    void LobbyStub::OnDisconnected()
    {
    }

    void LobbyStub::OnAccepted()
    {
        INFO_LOG("LobbyStub accepted ( LobbyStubId - {} )", m_id);
    }

    asio::awaitable<void> LobbyStub::Read(const uint8_t* pData, std::size_t dataSize)
    {
        using namespace Zozo;

        auto verifier = flatbuffers::Verifier(pData, dataSize);
        if (!VerifyLobbyGameMessageBuffer(verifier))
            co_return;

        auto message = Zozo::GetLobbyGameMessage(pData);
        NULL_CO_RETURN(message)

            flatbuffers::FlatBufferBuilder fbb;

        switch (message->payload_type())
        {
        case LobbyGamePayload::LobbyGamePayload_RegisterReq:
            {
                INFO_LOG("RegisterReq received");
            }
            break;
        case LobbyGamePayload::LobbyGamePayload_RegisterAck:
            {
                ERROR_LOG("Logic error");
            }
            break;
        default:
            {
                WARN_LOG("Unhandled message ( payload_type - %s )",
                    EnumNameLobbyGamePayload(message->payload_type()));
            }
            co_return;
        }

        m_pSocket->EnqueueMessage(fbb.GetBufferPointer(), fbb.GetSize());
    }
}
