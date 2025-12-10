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

		void SetUserCharacterIds( UserId userId, std::vector<CharacterId> characterIds);

		auto Get(CharacterId id) -> std::shared_ptr<Character>;
		auto Get(UserId id) -> std::vector<std::shared_ptr<Character>>;

		UserId GetUserId(CharacterId id);

		void RegiterToken(UserId userId, const std::string& token);
		bool IsValidUser(UserId userId, const std::string& token);

	private:
		auto _Get(CharacterId id) -> std::shared_ptr<Character>;

	private:
		std::shared_mutex m_lock;
		std::unordered_map<CharacterId, std::shared_ptr<Character>> m_characters;
		std::unordered_map<UserId, std::set<CharacterId>>           m_userIdCharacterIds;
		std::unordered_map<CharacterId, UserId>                     m_characterIdUserId;
		std::unordered_map<UserId, std::string>                     m_tokens;
	};
}
