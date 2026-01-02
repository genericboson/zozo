#pragma once

#include <shared_mutex>

#include "BroadCast.h"

namespace GenericBoson
{
	class Character;

	class Zone : public std::enable_shared_from_this<Zone>
	{
	public:
		virtual ~Zone() { }

		bool Enter(const std::shared_ptr< Character >& pCharacter);
		bool Leave(const int64_t id);

		bool _Enter(const std::shared_ptr< Character >& pCharacter);
		bool _Leave(const int64_t id);

		void Broadcast(const std::vector<std::unique_ptr<BroadCast>>& data);

	private:
		std::shared_mutex m_lock;
		int64_t m_id;
		std::unordered_map< int64_t, std::weak_ptr< Character > > m_characters;
	};
}