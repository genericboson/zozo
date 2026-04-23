#include "PCH.h"

#include <boost/mysql.hpp>
#include <boost/mysql/static_results.hpp>
#include <boost/mysql/pfr.hpp>

#include <format>

#include <Engine/Tx/MemObject.h>
#include <Engine/Tx/MemTx.h>
#include <Engine/Tx/Continuation.h>
#include <Engine/Tx/CustomAttributes.h>
#include <MessageSchema/Common/Type_generated.h>
#include <MessageSchema/External/GameServerMem/DB_GameServer.h>
#include <MessageSchema/External/GameServer_generated.h>

#include "Actor/Character/Character.h"
#include "Actor/Character/CharacterManager.h"
#include "Actor/ZoneManager.h"
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
        // copy token into a std::string so it remains valid after this function returns
        const std::string tokenStr = selectReq->token() ? selectReq->token()->c_str() : std::string();

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

        auto tx = NewTx();
        auto characterMem = tx->New<Zozo::CharacterMem<MemObject<Readable>>>();

        characterMem->GetUserId().SetKey(userId);
        characterMem->GetId().Bind();
        characterMem->GetName().Bind();
        characterMem->GetLevel().Bind();

        if (!characterMem->Select())
        {
            co_return;
        }

        DBResult dbResult{ .resultCode = Zozo::ResultCode::ResultCode_Success };
        if (!co_await characterMem->Execute(dbResult))
        {
            WARN_LOG("Failed to execute mem object.");//object name - {}",
            //characterMem->GetObjectName());
            co_return;
        }

        if (dbResult.pChacheObjects.size() != 1)
        {
            WARN_LOG("[CharacterSelectReq] Invalid DB scheme. token : {}, user id : {}", tokenStr, userId);
            const auto ack = Zozo::CreateCharacterSelectAck(fbb, Zozo::ResultCode_WrongDBSchema);
            const auto msg = Zozo::CreateGameMessage(fbb, Zozo::GamePayload_CharacterSelectAck, ack.Union());
            fbb.Finish(msg);

            co_return;
        }

        const auto& pCharacterMem = std::static_pointer_cast<Zozo::CharacterMem<MemObject<Readable>>>(dbResult.pChacheObjects[0]);

        if (!pCharacterMem)
        {
            WARN_LOG("[CharacterSelectReq] pCharacterMem is nullptr. token : {}, user id : {}", tokenStr, userId);
            const auto ack = Zozo::CreateCharacterSelectAck(fbb, Zozo::ResultCode_InvalidCharacterId);
            const auto msg = Zozo::CreateGameMessage(fbb, Zozo::GamePayload_CharacterSelectAck, ack.Union());
            fbb.Finish(msg);

            co_return;
        }

        if (const auto resultCode = CharacterManager::GetInstance()
            ->AddCharacter(shared_from_this(), pCharacterMem->GetId().Get());
            resultCode == Zozo::ResultCode_Success)
        {
            m_info.level = pCharacterMem->GetLevel().Get();
            m_info.name = pCharacterMem->GetName().Get();
            m_info.position = std::make_unique<Zozo::Vector2F>(m_position);

            // #todo - temporary test code. (0, 0) zone.
            ZoneManager::GetInstance()->EnterZone(shared_from_this(), 0, 0);
        }

        auto infoOffset = Zozo::CharacterInfo::Pack(fbb, &m_info);
        auto ack = Zozo::CreateCharacterSelectAck(fbb, Zozo::ResultCode_Success, infoOffset);
        auto msg = Zozo::CreateGameMessage(fbb, Zozo::GamePayload_CharacterSelectAck, ack.Union());

        fbb.Finish(msg);
        m_pSocket->EnqueueMessage(fbb.GetBufferPointer(), fbb.GetSize());

        co_return;
    }
}