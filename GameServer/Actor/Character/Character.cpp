#include "PCH.h"

#include <memory>

#include <boost/asio.hpp>
#include <boost/asio/use_awaitable.hpp>

#include <flatbuffers/flatbuffers.h>

#include <Engine/Socket/ISocket.h>
#include <Engine/Socket/BoostTcpSocket.h>

#include <MessageSchema/External/GameServer_generated.h>

#include "Character.h"
#include "CharacterManager.h"

namespace GenericBoson
{
    Character::Character(const std::shared_ptr<ISocket>& pSocket)
		: m_id(0), m_pSocket(pSocket)
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

        CharacterManager::GetInstance()->AddCharacter(shared_from_this());
        return true;
    }

    void Character::Write()
    {
    }

    void Character::OnDisconnected()
    {
    }

    void Character::OnAccepted()
    {
        INFO_LOG("Client accepted ( ClientId - {} )", m_id);
    }

    awaitable<void> Character::Read(const uint8_t* pData, std::size_t dataSize)
    {
        using namespace Zozo;

        auto verifier = flatbuffers::Verifier(pData, dataSize);
        if (!VerifyGameMessageBuffer(verifier))
            co_return;

        auto message = Zozo::GetGameMessage(pData);
        NULL_CO_RETURN(message)
        
        switch (message->payload_type())
        {
        case GamePayload::GamePayload_CharacterMoveReq:
            {
			    auto moveReq = message->payload_as_CharacterMoveReq();
                INFO_LOG("CharacterPos:{},{}", moveReq->x(), moveReq->y());
            }
            break;
        case GamePayload::GamePayload_CharacterMoveAck:
            {
			    ERROR_LOG("Logic error");
            }
            break;
        default:
            WARN_LOG("Unhandled message ( payload_type - %s )", 
                EnumNameGamePayload(message->payload_type()));
			break;
        }
    }
}
