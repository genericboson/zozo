#pragma once

namespace GenericBoson
{
	class Character;

	class Zone
	{
	public:
		virtual ~Zone() { }

		bool Enter(const std::shared_ptr< Character >& pCharacter);

		bool Leave(const int64_t id);

		void Broadcast();

	private:
		int64_t m_id;
		std::unordered_map< int64_t, std::shared_ptr< Character > > m_characters;
	};
}