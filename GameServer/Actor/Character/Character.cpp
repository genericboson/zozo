#include "PCH.h"

#include <memory>

#include <boost/asio.hpp>

#include <flatbuffers/flatbuffers.h>

#include <Engine/Socket/ISocket.h>
#include <Engine/Socket/BoostTcpSocket.h>

#include <MessageSchema/Connection_generated.h>
#include <MessageSchema/MessageId_generated.h>

#include "Character.h"

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

    bool Character::Initiailize()
    {
        if (!m_pSocket->IsValid())
            return false;

        HandleRead();
    }

    void Character::HandleRead()
    {
        m_pSocket->ReadHeader();
    }

    void Character::HandleWrite()
    {
    }

    void Character::OnDisconnected()
    {
    }

    void Character::ReadMessage(const uint32_t id, const uint8_t* pData, std::size_t dataSize)
    {
        using namespace Zozo;

        if (id > MessageId_MAX)
        {
			WARN_LOG("Invalid message id ( Id - %d )", id);
            return;
        }

        auto verifier = flatbuffers::Verifier(pData, dataSize);
        
        switch (static_cast<MessageId>(id))
        {
        case MessageId::MessageId_Connection:
            {
                
            }
            break;
        default:
            WARN_LOG("Unhandled message id ( Id - %d )", id);
			break;
        }
    }
}
