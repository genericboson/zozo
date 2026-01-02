#include "PCH.h"

#include <memory>

#include <Engine/Macros.h>

#include "Character/Character.h"
#include "Zone.h"

namespace GenericBoson
{
	bool Zone::Enter(const std::shared_ptr<Character>& pCharacter)
	{
		std::unique_lock lock(m_lock);
		return _Enter(pCharacter);
	}

	bool Zone::Leave(const int64_t id)
	{
		std::unique_lock lock(m_lock);
		return _Leave(id);
	}

	bool Zone::_Enter(const std::shared_ptr<Character>& pCharacter)
	{
		m_characters[pCharacter->Id()] = pCharacter->weak_from_this();
		pCharacter->m_wpZone = weak_from_this();
		return true;
	}

	bool Zone::_Leave(const int64_t id)
	{
		m_characters.erase(id);
		return true;
	}

	void Zone::Broadcast(const std::vector<std::unique_ptr<BroadCast>>& data)
	{
		std::shared_lock lock(m_lock);

		for (auto& pBroadcastData : data)
		{
			for (const auto& [id, wpCharacter] : m_characters)
			{
				if (pBroadcastData->senderCharacterId  == id)
					continue;

				auto pCharacter = wpCharacter.lock();

				NULL_CONTINUE(pCharacter);

				pBroadcastData->Cast(pCharacter);
			}
		}
	}
}