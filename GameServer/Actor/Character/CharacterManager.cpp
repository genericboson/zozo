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
		std::shared_lock<std::shared_mutex> lock{ m_lock };

		return _Get(id);
	}

	auto CharacterManager::Get(UserId id)
		-> std::vector<std::shared_ptr<Character>>
	{
		std::shared_lock<std::shared_mutex> lock{ m_lock };

		if (const auto found = m_userIdCharacterIds.find(id);
			found != m_userIdCharacterIds.end())
		{
			std::vector<std::shared_ptr<Character>> characters;
			for (const auto characterId : found->second)
			{
				characters.emplace_back(_Get(CharacterId{ characterId }));
			}

			return characters;
		}

		return {};
	}

	void CharacterManager::RegiterToken(UserId userId, const std::string& token)
	{
		std::unique_lock<std::shared_mutex> lock{ m_lock };
		m_tokens[userId] = token;
	}

	auto CharacterManager::_Get(CharacterId id) -> std::shared_ptr<Character>
	{
		if (const auto found = m_characters.find(id);
			found != m_characters.end())
			return found->second;

		return nullptr;
	}
}