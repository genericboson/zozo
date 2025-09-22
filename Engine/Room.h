#pragma once

namespace GenericBoson
{
	class Character;

	class Room
	{
	public:
		virtual ~Room() { }

		void Enter(const std::shared_ptr< Character >& pCharacter);

		void Leave(const int64_t id);

	private:
		int64_t m_id;
		std::unordered_map< int64_t, std::shared_ptr< Character > > m_characters;
	};
}