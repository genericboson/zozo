#include "PCH.h"

#include "Character.h"
#include "Room.h"

namespace GenericBoson
{
	bool Room::Enter(const std::shared_ptr<Character>& pCharacter)
	{
		NULL_RETURN(pCharacter, false);

		m_characters[pCharacter->Id()] = pCharacter;

		return true;
	}

	bool Room::Leave(const int64_t id)
	{
		NULL_RETURN(id, false);

		m_characters.erase(id);

		return true;
	}
}