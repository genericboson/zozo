#include "PCH.h"

#include <memory>

#include <boost/asio.hpp>

#include "Character.h"
#include <Engine/Socket/ISocket.h>
#include <Engine/Socket/BoostTcpSocket.h>

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
		auto self{ shared_from_this() };

        m_pSocket->Read();
    }

    void Character::HandleWrite()
    {
    }

    void Character::OnDisconnected()
    {
    }
}
