#include "PCH.h"

#include "Character.h"

namespace GenericBoson
{
    Character::Character(std::shared_ptr<ISocket> pSocket)
		: m_id(0), m_pSocket(pSocket)
    {
    }

    int64_t Character::Id() const
    {
        return m_id;
    }
}
