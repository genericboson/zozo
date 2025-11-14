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
        NULL_CO_RETURN(message)

        flatbuffers::FlatBufferBuilder fbb;

        switch (message->payload_type())
        {
        case LobbyPayload::LobbyPayload_AuthReq:
            {
                auto authReq = message->payload_as_AuthReq();
                NULL_CO_RETURN(authReq);

                const auto tmpUuid = boost::uuids::to_string(boost::uuids::random_generator()());

                INFO_LOG("[AuthReq] new token : {}", tmpUuid);

                const auto accountStr = authReq->account()->c_str();
                const auto passwordStr = authReq->password()->c_str();

                auto queryStr = mysql::with_params(
                    "START TRANSACTION;"
                    "SELECT password FROM zozo_lobby.user WHERE user.account = {};"
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
                    }
                    else
                    {
                        resultCode = Zozo::ResultCode::ResultCode_WrongPassword;
                    }
                }

                auto tokenOffset = fbb.CreateString(resultCode == Zozo::ResultCode::ResultCode_Success ? tmpUuid : "");
                auto authAck = Zozo::CreateAuthAck(fbb, resultCode, tokenOffset);
                auto lobbyMsg = Zozo::CreateLobbyMessage(fbb, Zozo::LobbyPayload_AuthAck, authAck.Union());

                fbb.Finish(lobbyMsg);
            }
            break;  
        case LobbyPayload::LobbyPayload_LoginReq:
            {
            using namespace std::chrono_literals;

			    auto loginReq = message->payload_as_LoginReq();
                NULL_CO_RETURN(loginReq);

                auto queryStr = mysql::with_params(
                    "SELECT uc.id AS character_id, uc.user_id AS user_id, uc.name AS name, uc.level AS level "
                    "FROM zozo_lobby.user JOIN zozo_lobby.user_character AS uc "
                    "ON user.id = uc.user_id "
                    "WHERE user.account = {} AND user.token = {};",
                    loginReq->account()->c_str(),
                    loginReq->token()->c_str());

                mysql::static_results<mysql::pfr_by_name<Join_User_UserCharacter>> result;
                if (auto [dbErr] = co_await m_server.m_pDbConn->async_execute(
                    queryStr,
                    result,
                    asio::as_tuple(asio::use_awaitable));
                    dbErr)
                {
                    ERROR_LOG("Query execute error. error code - {}({})", dbErr.value(), dbErr.message());
                    co_return;
                }

                std::vector<flatbuffers::Offset<Zozo::CharacterInfo>> characterInfos;
                if (result.rows().size() > 0)
                {
                    characterInfos.reserve(result.rows().size());
                    for (const auto& dbInfo : result.rows())
                    {
                        auto nameStrOffset = fbb.CreateString(*dbInfo.name);
                        auto info = Zozo::CreateCharacterInfo(fbb, *dbInfo.character_id, *dbInfo.user_id, nameStrOffset, *dbInfo.level);
                        characterInfos.emplace_back(std::move(info));
                    }
                }
                auto infosOffset = fbb.CreateVector(characterInfos);

                auto loginAck = Zozo::CreateLoginAck(fbb, Zozo::ResultCode_Success,0, infosOffset);
                auto lobbyMsg = Zozo::CreateLobbyMessage(fbb, Zozo::LobbyPayload_LoginAck, loginAck.Union());
                
                fbb.Finish(lobbyMsg);
            }
            break;
        case LobbyPayload::LobbyPayload_LoginAck:
            {
                ERROR_LOG("Logic error");
            }
            break;
        case LobbyGamePayload::LobbyGamePayload_RegisterReq:
        {

        }
            break;
        default:
            {
                WARN_LOG("Unhandled message ( payload_type - %s )",
                    EnumNameLobbyPayload(message->payload_type()));
            }
            co_return;
        }

        m_pSocket->EnqueueMessage(fbb.GetBufferPointer(), fbb.GetSize());
    }

    void LobbyUser::SendLoginAck()
    {
	}
}
