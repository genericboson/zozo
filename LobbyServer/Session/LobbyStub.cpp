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

        LobbyStubManager::GetInstance()->AddUnregisteredLobbyStub(shared_from_this());

        return true;
    }

    void LobbyStub::Write(const uint8_t* data, size_t size)
    {
        m_pSocket->EnqueueMessage(data, size);
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
        NULL_CO_RETURN(message);

        switch (message->payload_type())
        {
        case LobbyGamePayload::LobbyGamePayload_RegisterReq:
            {
                auto regReq = message->payload_as_RegisterReq();
                NULL_CO_RETURN(regReq);

                const auto serverId = regReq->server_id();

                auto queryStr = mysql::with_params(
                    "SELECT * FROM zozo_lobby.game_server WHERE id = {};"
                    , serverId );

                mysql::static_results<mysql::pfr_by_name<RegisterReq_Select_GameServer>> result;
                if (auto [dbErr] = co_await m_server.m_pDbConn->async_execute(
                    queryStr,
                    result,
                    asio::as_tuple(asio::use_awaitable));
                    dbErr)
                {
                    ERROR_LOG("Query execute error. error code - {}({})", dbErr.value(), dbErr.message());
                    co_return;
                }

                flatbuffers::FlatBufferBuilder fbb;

                auto resultCode = Zozo::ResultCode_NoData;
                if (result.rows().size() == 1)
                {
                    const auto dbInfo = *result.rows().begin();

                    auto dbIp         = fbb.CreateString(dbInfo.db_ip);
                    auto dbAccount    = fbb.CreateString(dbInfo.db_account);
                    auto dbPassword   = fbb.CreateString(dbInfo.db_password);
                    auto dbMainSchema = fbb.CreateString(dbInfo.db_main_schema);
                    auto serverName   = fbb.CreateString(dbInfo.server_name);

                    auto ack = Zozo::CreateRegisterAck(fbb, Zozo::ResultCode_Success, 
                        dbIp, dbAccount, dbPassword, dbMainSchema, serverName,
                        dbInfo.db_port, dbInfo.listen_port);
                    auto msg = Zozo::CreateLobbyGameMessage(fbb, Zozo::LobbyGamePayload_RegisterAck, ack.Union());
                    fbb.Finish(msg);

                    m_name   = dbInfo.server_name;

                    m_ip     = m_pSocket->GetRemoteIp();
                    m_port   = std::to_string( dbInfo.listen_port );
                    m_maxCCU = dbInfo.max_ccu;

                    LobbyStubManager::GetInstance()->AddRegisteredLobbyStub(shared_from_this(), serverId);

                    INFO_LOG("GameServer ( server id - {} ) registered. "
                        "dpIp - {}, dbAccount - {}, dbPassword - {}, dbMainSchema - {}, serverName - {}, "
                        "db_port - {}, listen_port - {}",
                        serverId, dbInfo.db_ip, dbInfo.db_account, dbInfo.db_password, 
                        dbInfo.db_main_schema, dbInfo.server_name, 
                        dbInfo.db_port, dbInfo.listen_port);

                    m_pSocket->EnqueueMessage(fbb.GetBufferPointer(), fbb.GetSize());

                    break;
                }

                if (result.rows().size() > 1)
                    resultCode = Zozo::ResultCode_LogicError;

                ERROR_LOG("GameServer register failed. server id - {}, error code - {}({})", 
                    serverId, static_cast<int>(resultCode), EnumNameResultCode(resultCode));

                auto ack = Zozo::CreateRegisterAck(fbb, resultCode);
                auto msg = Zozo::CreateLobbyGameMessage(fbb, Zozo::LobbyGamePayload_RegisterAck, ack.Union());
                fbb.Finish(msg);

                m_pSocket->EnqueueMessage(fbb.GetBufferPointer(), fbb.GetSize());
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
    }
}
