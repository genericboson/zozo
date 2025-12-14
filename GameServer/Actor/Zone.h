#pragma once

#include "BroadCastData.h"

namespace GenericBoson
{
	class Character;

	class Zone
	{
	public:
		virtual ~Zone() { }

		bool Enter(const std::weak_ptr< Character >& pCharacter, const int64_t characterId);

		bool Leave(const int64_t id);

		void Broadcast(const std::vector<BroadCastData>& data);

	private:
		std::shared_mutex m_lock;
		int64_t m_id;
		std::unordered_map< int64_t, std::weak_ptr< Character > > m_characters;
	};
}