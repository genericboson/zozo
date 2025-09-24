#include "PCH.h"

#include "Character.h"

namespace GenericBoson
{
    Character::Character(
        std::shared_ptr<ISocket> pSocket, 
        std::weak_ptr<Room>      wpRoom)
		: m_pSocket(pSocket), m_wpRoom(wpRoom)
    {
    }

    int64_t Character::Id() const
    {
        return m_id;
    }
}
