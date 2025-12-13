#include "PCH.h"

#include <Engine/Macros.h>

#include "Character/Character.h"
#include "Zone.h"

namespace GenericBoson
{
	bool Zone::Enter(const std::shared_ptr<Character>& pCharacter)
	{
		NULL_RETURN(pCharacter, false);

		m_characters[pCharacter->Id()] = pCharacter;

		return true;
	}

	bool Zone::Leave(const int64_t id)
	{
		NULL_RETURN(id, false);

		m_characters.erase(id);

		return true;
	}

	void Zone::Broadcast()
	{
	}
}