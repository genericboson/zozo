#include "PCH.h"

#include "Character.h"
#include "CharacterManager.h"

namespace GenericBoson
{
	void CharacterManager::AddCharacter(std::shared_ptr<Character>&& pCharacter)
	{
		m_characters[CharacterId{ pCharacter->Id() }] = pCharacter;
	}

	auto CharacterManager::Get(CharacterId id)
		-> std::shared_ptr<Character>
	{
		if(const auto found = m_characters.find(id);
			found != m_characters.end())
			return found->second;

		return nullptr;
	}

	auto CharacterManager::Get(UserId id)
		-> std::shared_ptr<Character>
	{
		/*if (const auto found = m_userIdCharacterIds.find(id);
			found != m_userIdCharacterIds.end())
		{
			if (const auto found = m_characters.find(found);
				found != m_userIdCharacterIds.end())
				return found->second;

			return nullptr;
		}*/

		return nullptr;
	}
}