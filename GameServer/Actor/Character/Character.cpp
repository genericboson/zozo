#include "PCH.h"

#include <memory>

#include <boost/asio.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/mysql.hpp>
#include <boost/mysql/static_results.hpp>
#include <boost/mysql/pfr.hpp>

#include <flatbuffers/flatbuffers.h>

#include <Engine/Numeric/IdGenerator.h>
#include <Engine/Socket/ISocket.h>
#include <Engine/Socket/BoostTcpSocket.h>

#include <MessageSchema/Common/Type_generated.h>
#include <MessageSchema/External/GameServer_generated.h>

#include "Actor/ZoneManager.h"
#include "GameServer.h"
#include "Character.h"
#include "CharacterManager.h"
#include "StaticResults.h"

namespace GenericBoson
{
    namespace mysql = boost::mysql;

    Character::Character(
        const std::shared_ptr<GameServer>& pServer,
        const std::shared_ptr<ISocket>&    pSocket)
		: m_id(0), m_server(*pServer), m_pSocket(pSocket)
    {
    }

    int64_t Character::Id() const
    {
        return m_id;
    }

    bool Character::Initialize()
    {
        if (!m_pSocket->IsValid())
            return false;

		CharacterManager::GetInstance()->AddUnselected(shared_from_this());

        return true;
    }

    void Character::Write(const uint8_t* pData, const std::size_t size)
    {
        m_pSocket->EnqueueMessage(pData, size);
    }

    void Character::OnDisconnected()
    {
        CharacterManager::GetInstance()->RemoveCharacter(shared_from_this());
    }

    void Character::OnAccepted()
    {
        INFO_LOG("Client accepted ( temporary id - {} )", m_id);
    }

    asio::awaitable<void> Character::Read(const uint8_t* pData, std::size_t dataSize)
    {
        using namespace Zozo;

        auto verifier = flatbuffers::Verifier(pData, dataSize);
        if (!VerifyGameMessageBuffer(verifier))
            co_return;

        auto message = Zozo::GetGameMessage(pData);
        NULL_CO_VOID_RETURN(message);

        switch (message->payload_type())
        {
        case GamePayload::GamePayload_CharacterListReq:
			co_await RecvCharacterListReq(message);
            break;
        case GamePayload::GamePayload_CharacterSelectReq:
            {
                auto selectReq = message->payload_as_CharacterSelectReq();
                NULL_CO_VOID_RETURN(selectReq);

                flatbuffers::FlatBufferBuilder fbb;

				const auto characterId = selectReq->id();
				const auto tokenStr    = selectReq->token()->c_str();

				const int64_t userId   = CharacterManager::GetInstance()->GetUserId(CharacterId{ characterId });
                if (!userId)
                {
                    WARN_LOG("[Invalid CharacterId]  token : {}, user id : {}", tokenStr, userId);
                    const auto ack = Zozo::CreateCharacterSelectAck(fbb, Zozo::ResultCode_InvalidCharacterId);
                    const auto msg = Zozo::CreateGameMessage(fbb, Zozo::GamePayload_CharacterSelectAck, ack.Union());
                    fbb.Finish(msg);
                    break;
                }

                if (!CharacterManager::GetInstance()->IsValidUser(UserId{ userId }, tokenStr))
                {
                    WARN_LOG("[Invalid CharacterSelectReq]  token : {}, user id : {}", tokenStr, userId);
                    const auto ack = Zozo::CreateCharacterSelectAck(fbb, Zozo::ResultCode_InvalidToken);
                    const auto msg = Zozo::CreateGameMessage(fbb, Zozo::GamePayload_CharacterSelectAck, ack.Union());
                    fbb.Finish(msg);
                    break;
                }

                INFO_LOG("[CharacterSelectReq] token : {}", tokenStr);

                auto queryStr = mysql::with_params(
                    "SELECT id, name, level FROM zozo_game.character WHERE id = {};", characterId);

				// #todo change to CharacterSelect_Select_UserCharacter
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
				m_pSocket->EnqueueMessage(fbb.GetBufferPointer(), fbb.GetSize());
            }
            break;
        case GamePayload::GamePayload_CharacterSelectAck:
            {
                ERROR_LOG("Logic error");
            }
            break;
        case GamePayload::GamePayload_CharacterPositionUpdateReq:
            {
			    auto moveReq = message->payload_as_CharacterPositionUpdateReq();

                //INFO_LOG("CharacterPos:{},{},{},{}",
                //    moveReq->position()->x(), moveReq->position()->y(), 
                //    Zozo::EnumNameDirection(moveReq->direction()), moveReq->is_moved());

                if (const auto pZone = m_wpZone.lock())
                {
                    PositionCast castData;
					castData.senderCharacterId = m_id;
					castData.position = Vector2F( moveReq->position()->x(), moveReq->position()->y() );
					castData.direction = moveReq->direction();
					castData.isMoved = moveReq->is_moved();

					std::vector<std::unique_ptr<BroadCast>> broadcasts;

					broadcasts.emplace_back(std::make_unique<PositionCast>(castData));

                    pZone->Broadcast(broadcasts);
                }
            }
            break;
        case GamePayload::GamePayload_CharacterPositionUpdateAck:
            {
			    ERROR_LOG("Logic error");
            }
            break;
        case GamePayload::GamePayload_CharacterCreateReq:
            {
                m_id = GenericBoson::IdGenerator::CreateId(m_server.m_id);
            }
            break;
        case GamePayload::GamePayload_CharacterCreateAck:
            {
                ERROR_LOG("Logic error");
            }
            break;
        default:
            WARN_LOG("Unhandled message ( payload_type - {} )", 
                EnumNameGamePayload(message->payload_type()));
			break;
        }
    }
}
