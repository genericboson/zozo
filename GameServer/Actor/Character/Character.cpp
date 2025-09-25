#include "PCH.h"

#include "Character.h"

namespace GenericBoson
{
    Character::Character(
        std::shared_ptr<ISocket> pSocket, 
        std::weak_ptr<Zone>      wpZone)
		: m_pSocket(pSocket), m_wpZone(wpZone)
    {
    }

    int64_t Character::Id() const
    {
        return m_id;
    }
}
