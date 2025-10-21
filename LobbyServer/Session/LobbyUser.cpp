#include "PCH.h"

#include <memory>

#include <boost/asio.hpp>
#include <boost/mysql.hpp>
#include <boost/mysql/static_results.hpp>
#include <boost/mysql/pfr.hpp>

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

    awaitable<void> LobbyUser::Read(const uint8_t* pData, std::size_t dataSize)
    {
        using namespace Zozo;

        auto verifier = flatbuffers::Verifier(pData, dataSize);
        if (!VerifyLobbyMessageBuffer(verifier))
            co_return;

        auto message = Zozo::GetLobbyMessage(pData);
        NULL_CO_RETURN(message)

        switch (message->payload_type())
        {
        case LobbyPayload::LobbyPayload_LoginReq:
            {
            using namespace std::chrono_literals;

			    auto loginReq = message->payload_as_LoginReq();
                NULL_CO_RETURN(loginReq);

                auto [connErr, conn] = co_await m_server.m_dbConnPool.async_get_connection(
                    asio::cancel_after(10s, // #todo get from environment variable
                        asio::as_tuple(asio::use_awaitable)));
                if (connErr != boost::system::errc::success)
                {
                    ERROR_LOG("Get DB connection from pool failed. error code - {}({})", connErr.value(), connErr.message());
                    co_return;
                }

                mysql::static_results<mysql::pfr_by_name<Join_User_UserCharacter>> result;
                if (auto [dbErr] = co_await conn->async_execute(
                    mysql::with_params("SELECT character_id AS user_characer.id, user_id, name, level FROM user "
                        "JOIN user_character ON user.id = user_character.user_id "
                        "WHERE account = {} AND password = {}", 
                        loginReq->account()->c_str(), 
                        loginReq->password()->c_str()),
                    result,
                    asio::as_tuple(asio::use_awaitable));
                    dbErr)
                {
                    ERROR_LOG("Query execute error. error code - {}({})", dbErr.value(), dbErr.message());
                    co_return;
                }

                flatbuffers::FlatBufferBuilder fbb;

                std::vector<flatbuffers::Offset<Zozo::CharacterInfo>> characterInfos;
                if (result.rows().size() > 0)
                {
                    characterInfos.reserve(result.rows().size());
                    for (const auto& dbInfo : result.rows())
                    {
                        auto nameStrOffset = fbb.CreateString(dbInfo.name);
                        auto info = Zozo::CreateCharacterInfo(fbb, dbInfo.character_id, dbInfo.user_id, nameStrOffset, dbInfo.level);
                        characterInfos.emplace_back(std::move(info));
                    }
                }
                auto infosOffset = fbb.CreateVector(characterInfos);

                auto loginAck = Zozo::CreateLoginAck(fbb, Zozo::ResultCode_Success,0, infosOffset);
                auto lobbyMsg = Zozo::CreateLobbyMessage(fbb, Zozo::LobbyPayload_LoginAck, loginAck.Union());
                fbb.Finish(lobbyMsg);

                m_pSocket->EnqueueMessage(fbb.GetBufferPointer(), fbb.GetSize());
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
	}
}
