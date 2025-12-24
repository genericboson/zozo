#include "PCH.h"

#include <Engine/Macros.h>

#include "Character/Character.h"
#include "Zone.h"

namespace GenericBoson
{
	bool Zone::Enter(const std::weak_ptr<Character>& pCharacter, const int64_t characterId)
	{
		NULL_RETURN(characterId, false);

		std::unique_lock lock(m_lock);
		m_characters[characterId] = pCharacter;
		return true;
	}

	bool Zone::Leave(const int64_t id)
	{
		NULL_RETURN(id, false);

		std::unique_lock lock(m_lock);
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