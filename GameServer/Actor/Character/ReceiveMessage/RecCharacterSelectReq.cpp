#include "PCH.h"

#include <boost/mysql.hpp>
#include <boost/mysql/static_results.hpp>
#include <boost/mysql/pfr.hpp>

#include <format>

#include <Engine/Tx/MemObject.h>
#include <Engine/Tx/MemTx.h>
#include <Engine/Tx/Continuation.h>
#include <Engine/Tx/CustomAttributes.h>
#include <MessageSchema/External/GameServerMem/DB_GameServer.h>
#include <MessageSchema/External/GameServer_generated.h>

#include "Actor/Character/Character.h"
#include "Actor/Character/CharacterManager.h"
#include "GameServer.h"
#include "StaticResults.h"

namespace GenericBoson
{
    namespace mysql = boost::mysql;

    asio::awaitable<void> Character::RecvCharacterSelectReq(const Zozo::GameMessage* message)
    {
        auto selectReq = message->payload_as_CharacterSelectReq();
        NULL_CO_VOID_RETURN(selectReq);

        flatbuffers::FlatBufferBuilder fbb;

        const auto characterId = selectReq->id();
        const auto tokenStr = selectReq->token()->c_str();

        const int64_t userId = CharacterManager::GetInstance()->GetUserId(CharacterId{ characterId });
        if (!userId)
        {
            WARN_LOG("[Invalid CharacterId]  token : {}, user id : {}", tokenStr, userId);
            const auto ack = Zozo::CreateCharacterSelectAck(fbb, Zozo::ResultCode_InvalidCharacterId);
            const auto msg = Zozo::CreateGameMessage(fbb, Zozo::GamePayload_CharacterSelectAck, ack.Union());
            fbb.Finish(msg);
            co_return;
        }

        if (!CharacterManager::GetInstance()->IsValidUser(UserId{ userId }, tokenStr))
        {
            WARN_LOG("[Invalid CharacterSelectReq]  token : {}, user id : {}", tokenStr, userId);
            const auto ack = Zozo::CreateCharacterSelectAck(fbb, Zozo::ResultCode_InvalidToken);
            const auto msg = Zozo::CreateGameMessage(fbb, Zozo::GamePayload_CharacterSelectAck, ack.Union());
            fbb.Finish(msg);
            co_return;
        }

        INFO_LOG("[CharacterSelectReq] token : {}", tokenStr);

        auto queryStr = mysql::with_params(
            "SELECT id, name, level FROM zozo_game.character WHERE id = {};", characterId);

        // #todo change to CharacterSelect_Select_UserCharacter
        /*mysql::static_results<mysql::pfr_by_name<CharacterList_Select_UserCharacter>> result;
        if (auto [dbErr] = co_await m_server.m_pDbConn->async_execute(
            queryStr,
            result,
            asio::as_tuple(asio::use_awaitable));
            dbErr)
        {
            ERROR_LOG("Query execute error. error code - {}({})", dbErr.value(), dbErr.message());
            co_return;
        }

        auto selectResults = result.rows<0>();
        if (selectResults.size() <= 0)
        {
            WARN_LOG("[CharacterSelectReq] NoData. token : {}, user id : {}", tokenStr, userId);
            const auto ack = Zozo::CreateCharacterSelectAck(fbb, Zozo::ResultCode_NoData);
            const auto msg = Zozo::CreateGameMessage(fbb, Zozo::GamePayload_CharacterSelectAck, ack.Union());
            fbb.Finish(msg);
            co_return;
        }
        else if (selectResults.size() > 1)
        {
            WARN_LOG("[CharacterSelectReq] Wrong db schema. token : {}, user id : {}", tokenStr, userId);
            const auto ack = Zozo::CreateCharacterSelectAck(fbb, Zozo::ResultCode_WrongDBSchema);
            const auto msg = Zozo::CreateGameMessage(fbb, Zozo::GamePayload_CharacterSelectAck, ack.Union());
            fbb.Finish(msg);
            co_return;
        }

        const auto resultCode = co_await CharacterManager::GetInstance()
            ->AddCharacter(shared_from_this(), characterId);

        if (resultCode == Zozo::ResultCode_Success)
        {
            const auto& selectResult = selectResults[0];
            m_info.level = selectResult.level.value_or(0);
            m_info.name = selectResult.name.value_or("");
            m_info.position = std::make_unique<Vector2F>(m_position);

            // #todo - temporary test code. (0, 0) zone.
            ZoneManager::GetInstance()->EnterZone(shared_from_this(), 0, 0);
        }

        auto infoOffset = Zozo::CharacterInfo::Pack(fbb, &m_info);
        auto ack = Zozo::CreateCharacterSelectAck(fbb, resultCode, infoOffset);
        auto msg = Zozo::CreateGameMessage(fbb, Zozo::GamePayload_CharacterSelectAck, ack.Union());

        fbb.Finish(msg);
        m_pSocket->EnqueueMessage(fbb.GetBufferPointer(), fbb.GetSize());*/
    }
}