#pragma once

#include <Engine/Singleton.h>

namespace GenericBoson
{
	class Character;

	class CharacterManager : public Singleton< CharacterManager >
	{
	public:
		void AddCharacter(std::shared_ptr< Character >&& pCharacter);

	private:
		std::unordered_map< int64_t, std::shared_ptr< Character > > m_characters;
	};
}