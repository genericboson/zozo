#include "PCH.h"

#include <format>

#include <MessageSchema/Common/Type_generated.h>
#include <MessageSchema/External/GameServer_generated.h>

#include "Actor/BroadCast.h"
#include "Actor/Character/Character.h"
#include "Actor/Character/CharacterManager.h"
#include "Actor/Zone.h"
#include "Actor/ZoneManager.h"

namespace GenericBoson
{
    namespace mysql = boost::mysql;

    void Character::RecvCharacterPositionUpdateReq(const Zozo::GameMessage* message)
    {
        auto moveReq = message->payload_as_CharacterPositionUpdateReq();

        //INFO_LOG("CharacterPos:{},{},{},{}",
        //    moveReq->position()->x(), moveReq->position()->y(), 
        //    Zozo::EnumNameDirection(moveReq->direction()), moveReq->is_moved());

        if (const auto pZone = m_wpZone.lock())
        {
            PositionCast castData;
            castData.senderCharacterId = m_id;
            castData.position = Zozo::Vector2F(moveReq->position()->x(), moveReq->position()->y());
            castData.direction = moveReq->direction();
            castData.isMoved = moveReq->is_moved();

            std::vector<std::unique_ptr<BroadCast>> broadcasts;

            broadcasts.emplace_back(std::make_unique<PositionCast>(castData));

            pZone->Broadcast(broadcasts);
        }
    }
}