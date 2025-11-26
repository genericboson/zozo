#pragma once

#include <Engine/Singleton.h>

namespace GenericBoson
{
	enum CharacterId : int64_t;
	enum UserId : int64_t;

	class Character;

	class CharacterManager : public Singleton< CharacterManager >
	{
	public:
		void AddCharacter(std::shared_ptr< Character >&& pCharacter);

		auto Get(CharacterId id) -> std::shared_ptr<Character>;
		auto Get(UserId id) -> std::shared_ptr<Character>;

	private:
		std::unordered_map<CharacterId, std::shared_ptr<Character>> m_characters;
		std::unordered_map<UserId, std::set<CharacterId>> m_userIdCharacterIds;
	};
}
