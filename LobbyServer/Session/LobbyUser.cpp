#include "PCH.h"

#include <memory>

#include <boost/asio.hpp>

#include <flatbuffers/flatbuffers.h>

#include <Engine/Socket/ISocket.h>
#include <Engine/Socket/BoostTcpSocket.h>
#include <Engine/Tx/Continuation.h>

#include "CharacterInfo_generated.h"
#include <MessageSchema/External/LobbyServer_generated.h>
#include <MessageSchema/Internal/DBCache_generated.h>

#include <DBCacheClient/DBCacheClient.h>

#include "LobbyServer.h"
#include "LobbyUser.h"
#include "LobbyUserManager.h"

namespace GenericBoson
{
    LobbyUser::LobbyUser(
        LobbyServer& lobbyServer, 
        const std::shared_ptr<ISocket>& pSocket)
        : m_id(0), m_server(lobbyServer), m_pSocket(pSocket)
    {
    }

    int64_t LobbyUser::Id() const
    {
        return m_id;
    }

    bool LobbyUser::Initialize()
    {
        if (!m_pSocket->IsValid())
            return false;

        LobbyUserManager::GetInstance()->AddLobbyUser(shared_from_this());
        return true;
    }

    void LobbyUser::Write()
    {
    }

    void LobbyUser::OnDisconnected()
    {
    }

    void LobbyUser::OnAccepted()
    {
        INFO_LOG("LobbyUser accepted ( LobbyUserId - {} )", m_id);
    }

    awaitable<void> LobbyUser::Read(const uint8_t* pData, std::size_t dataSize)
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

                //m_server.
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

    void LobbyUser::SendLoginAck()
    {
        //// for debug
        //flatbuffers::FlatBufferBuilder fbb;
        //auto gameserverIp = fbb.CreateString("127.0.0.1");
        //auto gameserverPort = fbb.CreateString("8001");
        //auto token = fbb.CreateString("TestTokenA");
        //auto loginDBAck = Zozo::CreateLoginDBAck(
        //    fbb, Zozo::ResultCode_Success,
        //    gameserverIp, gameserverPort, token);
        //auto lobbyMsg = Zozo::CreateDBCacheLobbyMessage(fbb,
        //    Zozo::DBCacheLobbyPayload_LoginDBAck, loginDBAck.Union());
        //fbb.Finish(lobbyMsg);

        //m_pSocket->EnqueueMessage(fbb.GetBufferPointer(), fbb.GetSize());
	}
}
