#include "PCH.h"

#include <boost/mysql.hpp>
#include <boost/mysql/static_results.hpp>
#include <boost/mysql/pfr.hpp>

#include <format>

#include <Engine/Tx/CacheObject.h>
#include <Engine/Tx/CacheTx.h>
#include <Engine/Tx/Continuation.h>
#include <Engine/Tx/CustomAttributes.h>
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

        auto tx = NewTx();

        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        // [1] pre-processing

        auto characterCache = tx->New<Zozo::CharacterCache<CacheObject<Readable>>>();

        characterCache->GetUserId().SetKey(userId);
        characterCache->GetId().Bind();
        characterCache->GetName().Bind();
        
        if (!characterCache->Select())
        {
            co_return;
        }

        tx->RunAsync() | 
        [ this, userId ](DBResult dbResult) -> asio::awaitable<bool>
        {
            std::vector<CharacterId> characterIds;
            characterIds.reserve(dbResult.pChacheObjects.size());

            flatbuffers::FlatBufferBuilder fbb;
            std::vector<flatbuffers::Offset<Zozo::CharacterPairData>> pairDatas;

			for (const auto pObj : dbResult.pChacheObjects)
            {
                auto pCharacterCache = std::static_pointer_cast<Zozo::CharacterCache<CacheObject<Readable>>>(pObj);
                NULL_CONTINUE( pCharacterCache);

                const auto characterId = pCharacterCache->GetId().Get();

                characterIds.push_back(CharacterId{characterId});

                auto name = fbb.CreateString(std::format("{} [Lv.{}]", pCharacterCache->GetName().Get(), "11"));

                auto characterDataPair = Zozo::CreateCharacterPairData(fbb, characterId, name);
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

            co_return true;
        };
        
        INFO_LOG("[CharacterListReq] token : {}", tokenStr);

        co_return;
	}
}