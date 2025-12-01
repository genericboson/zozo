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
#include <MessageSchema/External/LobbyServer_generated.h>
#include <MessageSchema/Internal/LobbyGame_generated.h>

#include "LobbyServer.h"
#include "LobbyStub.h"
#include "LobbyStubManager.h"
#include "LobbyUser.h"
#include "LobbyUserManager.h"
#include "StaticResults.h"

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

    asio::awaitable<void> LobbyUser::Read(const uint8_t* pData, std::size_t dataSize)
    {
        using namespace Zozo;

        auto verifier = flatbuffers::Verifier(pData, dataSize);
        if (!VerifyLobbyMessageBuffer(verifier))
            co_return;

        auto message = Zozo::GetLobbyMessage(pData);
        NULL_CO_RETURN(message);

        flatbuffers::FlatBufferBuilder userFbb;

        switch (message->payload_type())
        {
        case LobbyPayload::LobbyPayload_ServerListReq:
            {
                auto listReq = message->payload_as_ServerListReq();
                NULL_CO_RETURN(listReq);

                const auto infos = LobbyStubManager::GetInstance()->GetServerInfos(userFbb);
                
                auto infosVector = userFbb.CreateVector(infos);

                auto ack = Zozo::CreateServerListAck(userFbb, Zozo::ResultCode_Success, infosVector);
                auto msg = Zozo::CreateLobbyMessage(userFbb, Zozo::LobbyPayload::LobbyPayload_ServerListAck, ack.Union());

                userFbb.Finish(msg);
            }
            break;
        case LobbyPayload::LobbyPayload_ServerListAck:
            {
                ERROR_LOG("Logic Error");
            }
            break;
        case LobbyPayload::LobbyPayload_AuthReq:
            {
                auto authReq = message->payload_as_AuthReq();
                NULL_CO_RETURN(authReq);

                const auto tmpUuid = boost::uuids::to_string(boost::uuids::random_generator()());

                INFO_LOG("[AuthReq] new token : {}", tmpUuid);

                const auto accountStr  = authReq->account()->c_str();
                const auto passwordStr = authReq->password()->c_str();
                const auto serverId    = authReq->server_id();

                auto queryStr = mysql::with_params(
                    "START TRANSACTION;"
                    "SELECT password, id FROM zozo_lobby.user WHERE user.account = {};"
                    "UPDATE zozo_lobby.user SET token = {} WHERE user.account = {} AND user.password = {};"
                    "COMMIT",
                    accountStr,
                    tmpUuid, accountStr, passwordStr);

                mysql::static_results<
                    std::tuple<>,
                    mysql::pfr_by_name<AuthReq_Select_User>,
                    std::tuple<>,
                    std::tuple<>> result;

                if (auto [dbErr] = co_await m_server.m_pDbConn->async_execute(
                    queryStr,
                    result,
                    asio::as_tuple(asio::use_awaitable));
                    dbErr)
                {
                    ERROR_LOG("Query execute error. error code - {}({})", dbErr.value(), dbErr.message());
                    co_return;
                }

                auto resultCode = Zozo::ResultCode::ResultCode_LogicError;
                
                int64_t userId{};
                std::string gameIp, gamePort;
                if (auto selectResults = result.rows<1>();
                    selectResults.size() == 0)
                {
                    resultCode = Zozo::ResultCode::ResultCode_NewAccount;
                }
                else if (selectResults.size() == 1)
                {
                    const AuthReq_Select_User& selectResult = *selectResults.begin();
                    if (selectResult.password.value_or("") == passwordStr)
                    {
                        resultCode = Zozo::ResultCode::ResultCode_Success;
                        userId = selectResult.id;

                        if (const auto relayResult = LobbyStubManager::GetInstance()->SendAuthRelay(serverId, userId, tmpUuid))
                        {
                            std::tie(gameIp, gamePort) = *relayResult;
                            INFO_LOG("Auth relay sent to server ( serverId - {}, userId - {} , ip - {}, port - {} )",
								serverId, userId, gameIp, gamePort);
                        }
                        else
                        {
							WARN_LOG("No allowed server suggested by client ( serverId - {} )", serverId);
                            resultCode = Zozo::ResultCode::ResultCode_NotAllowedServer;
                        }
                    }
                    else
                    {
                        resultCode = Zozo::ResultCode::ResultCode_WrongPassword;
                    }
                }

				flatbuffers::Offset<flatbuffers::String> tokenOffset = 0, ipOffset = 0, portOffset = 0;
                if (resultCode == Zozo::ResultCode::ResultCode_Success || 
                    resultCode == Zozo::ResultCode::ResultCode_NewAccount)
                {
                    tokenOffset = userFbb.CreateString(resultCode == Zozo::ResultCode::ResultCode_Success ? tmpUuid : "");
					ipOffset    = userFbb.CreateString(gameIp);
					portOffset  = userFbb.CreateString(gamePort);
                }
                auto authAck = Zozo::CreateAuthAck(userFbb, resultCode, userId, tokenOffset, ipOffset, portOffset);
                auto lobbyMsg = Zozo::CreateLobbyMessage(userFbb, Zozo::LobbyPayload_AuthAck, authAck.Union());

                userFbb.Finish(lobbyMsg);
            }
            break;
        default:
            {
                WARN_LOG("Unhandled message ( payload_type - {} )",
                    EnumNameLobbyPayload(message->payload_type()));
            }
            co_return;
        }

        m_pSocket->EnqueueMessage(userFbb.GetBufferPointer(), userFbb.GetSize());
    }

    void LobbyUser::SendLoginAck()
    {
	}
}
