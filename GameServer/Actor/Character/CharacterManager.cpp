#include "PCH.h"

#include "Character.h"
#include "CharacterManager.h"

namespace GenericBoson
{
	void CharacterManager::AddCharacter(std::shared_ptr<Character>&& pCharacter)
	{
		m_characters[pCharacter->Id()] = pCharacter;
	}
}