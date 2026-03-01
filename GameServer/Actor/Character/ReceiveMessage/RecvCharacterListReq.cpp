#include "PCH.h"

#include <boost/mysql.hpp>
#include <boost/mysql/static_results.hpp>
#include <boost/mysql/pfr.hpp>

#include <Engine/Tx/CacheTx.h>
#include <Engine/Tx/Continuation.h>
#include <MessageSchema/External/GameServerCache/DB_GameServer.h>
#include <MessageSchema/External/GameServer_generated.h>

#include "Actor/Character/Character.h"
#include "Actor/Character/CharacterManager.h"
#include "GameServer.h"
#include "StaticResults.h"

namespace GenericBoson
{
    namespace mysql = boost::mysql;

    asio::awaitable<void> Character::RecvCharacterListReq(const Zozo::GameMessage* message)
	{
        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        // [1] validation

        auto req = message->payload_as_CharacterListReq();
        NULL_CO_VOID_RETURN(req);

        const auto userId = req->user_id();
        const auto tokenStr = req->token()->c_str();

        flatbuffers::FlatBufferBuilder fbb;

        if (!CharacterManager::GetInstance()->IsValidUser(UserId{ userId }, tokenStr))
        {
            WARN_LOG("[Invalid CharacterListReq]  token : {}, user id : {}", tokenStr, userId);
            const auto ack = Zozo::CreateCharacterListAck(fbb, Zozo::ResultCode_InvalidToken);
            const auto msg = Zozo::CreateGameMessage(fbb, Zozo::GamePayload_CharacterListAck, ack.Union());
            fbb.Finish(msg);
            co_return;
        }

        auto tx = std::make_shared<CacheTx>(*this);

        auto characterCache = tx->New<GenericBoson::Zozo::CharacterCache>();

        characterCache->GetUserId().SetKey(userId);
        characterCache->GetId().Bind();
        characterCache->GetName().Bind();

        characterCache->Select();

        tx | [](void) ->asio::awaitable<bool> { co_return true; };

        tx->RunTx();
        
        INFO_LOG("[CharacterListReq] token : {}", tokenStr);

        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        // [2] db

        auto queryStr = mysql::with_params(
            "SELECT id, name FROM zozo_game.character WHERE user_id = {};",
            userId);

        mysql::static_results<mysql::pfr_by_name<CharacterList_Select_UserCharacter>> result;
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
            WARN_LOG("[CharacterListReq] NoData. token : {}, user id : {}", tokenStr, userId);
            const auto ack = Zozo::CreateCharacterListAck(fbb, Zozo::ResultCode_NoData);
            const auto msg = Zozo::CreateGameMessage(fbb, Zozo::GamePayload_CharacterListAck, ack.Union());
            fbb.Finish(msg);
            co_return;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        // [3] serialization

        std::vector<flatbuffers::Offset<Zozo::CharacterPairData>> pairDatas;

        std::vector<CharacterId> characterIds;
        characterIds.reserve(selectResults.size());
        for (auto& selectResult : selectResults)
        {
            characterIds.push_back(CharacterId{ selectResult.id });

            auto name = fbb.CreateString(std::format("{} [Lv.{}]",
                selectResult.name.value_or(""),
                "11"));//selectResult.level.value_or(0)));

            auto characterDataPair = Zozo::CreateCharacterPairData(fbb, selectResult.id, name);
            pairDatas.emplace_back(std::move(characterDataPair));
        }

        CharacterManager::GetInstance()->SetUserCharacterIds(
            UserId{ userId },
            std::move(characterIds));

        const auto pairDatasOffset = fbb.CreateVector(pairDatas);

        const auto ack = Zozo::CreateCharacterListAck(fbb, Zozo::ResultCode_Success, pairDatasOffset);
        const auto msg = Zozo::CreateGameMessage(fbb, Zozo::GamePayload_CharacterListAck, ack.Union());

        fbb.Finish(msg);

        ////////////////////////////////////////////////////////////////////////////////////////////////////////

        m_pSocket->EnqueueMessage(fbb.GetBufferPointer(), fbb.GetSize());

        co_return;
	}
}