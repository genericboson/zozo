#pragma once

#include <shared_mutex>

#include <boost/asio/awaitable.hpp>

#include <Engine/Singleton.h>

namespace GenericBoson
{
	namespace asio = boost::asio;

	class Character;
	class Zone;

	class ZoneManager : public GenericBoson::Singleton< ZoneManager >
	{
	public:
		asio::awaitable<bool> Initialize();

		bool EnterZone(const std::shared_ptr<Character>& pCharacter, const int64_t x, const int64_t y);
	private:
		std::shared_mutex m_lock;
		std::unordered_map<int64_t, std::unordered_map<int64_t, std::shared_ptr<Zone>>> m_zones;
	};
}