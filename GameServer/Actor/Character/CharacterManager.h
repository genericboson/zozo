#pragma once

namespace GenericBoson
{
	class Character;

	class CharacterManager : public Singleton< CharacterManager >
	{
	public:
	private:
		std::unordered_map< int64_t, std::shared_ptr< Character > > m_characters;
	};
}