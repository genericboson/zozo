#include "PCH.h"

#include <boost/mysql.hpp>
#include <boost/mysql/static_results.hpp>
#include <boost/mysql/pfr.hpp>

#include "Character.h"
#include "CharacterManager.h"

namespace GenericBoson
{
	namespace mysql = boost::mysql;

	void CharacterManager::AddUnselected(std::shared_ptr<Character>&& pCharacter)
	{
		const auto checkAlreadyOccupied = [this]() {
			if (m_unselecteds.contains(m_unselectedCount) &&
				m_unselecteds[m_unselectedCount] != nullptr)
			{
				ERROR_LOG("Already occupied unselected character map index : {}", m_unselectedCount);
				return false;
			}
			return true;
			};

		{
			std::shared_lock<std::shared_mutex> lock(m_lock);

			if (!checkAlreadyOccupied())
				return;
		}


		std::unique_lock<std::shared_mutex> lock{ m_lock };

		if (!checkAlreadyOccupied())
			return;

		pCharacter->m_temporaryId = m_unselectedCount;
		m_unselecteds[m_unselectedCount] = pCharacter;

		if (m_unselectedCount == std::numeric_limits<decltype(m_unselectedCount)>::max())
		{
			m_unselectedCount = 1;
			return;
		}
		m_unselectedCount++;
	}

	asio::awaitable<Zozo::ResultCode> CharacterManager::AddCharacter(std::shared_ptr<Character>&& pCharacter, int64_t characterId)
	{
		std::unique_lock<std::shared_mutex> lock{ m_lock };

		const auto newId = CharacterId{ characterId };

		pCharacter->m_id = characterId;

		if (m_characters.contains(newId))
			co_return Zozo::ResultCode::ResultCode_AlreadyLoggedIn;

		m_characters[newId] = pCharacter;
		m_unselecteds.erase(pCharacter->m_temporaryId);
		co_return Zozo::ResultCode::ResultCode_Success;
	}

	void CharacterManager::RemoveCharacter(std::shared_ptr<Character>&& pCharacter)
	{
		std::unique_lock<std::shared_mutex> lock(m_lock);

		m_characters.erase(CharacterId{ pCharacter->m_id });
		m_unselecteds.erase(pCharacter->m_temporaryId);
	}

	void CharacterManager::SetUserCharacterIds(UserId userId, std::vector<CharacterId> characterIds)
	{
		std::unique_lock<std::shared_mutex> lock{ m_lock };

		std::set<CharacterId> characterIdSet;
		for (const auto characterId : characterIds)
		{
			characterIdSet.insert(characterId);
			m_characterIdUserId[characterId] = userId;
		}
		m_userIdCharacterIds[userId] = std::move(characterIdSet);
	}

	auto CharacterManager::Get(CharacterId id)
		-> std::shared_ptr<Character>
	{
		std::shared_lock<std::shared_mutex> lock{ m_lock };

		return _Get(id);
	}

	auto CharacterManager::Get(UserId id)
		-> std::vector<std::shared_ptr<Character>>
	{
		std::shared_lock<std::shared_mutex> lock{ m_lock };

		if (const auto found = m_userIdCharacterIds.find(id);
			found != m_userIdCharacterIds.end())
		{
			std::vector<std::shared_ptr<Character>> characters;
			for (const auto characterId : found->second)
			{
				characters.emplace_back(_Get(CharacterId{ characterId }));
			}

			return characters;
		}

		return {};
	}

	UserId CharacterManager::GetUserId(CharacterId id)
	{
		std::shared_lock<std::shared_mutex> lock{ m_lock };
		if (const auto found = m_characterIdUserId.find(id);
			found != m_characterIdUserId.end())
			return found->second;

		return UserId{ 0 };
	}

	void CharacterManager::RegiterToken(UserId userId, const std::string& token)
	{
		std::unique_lock<std::shared_mutex> lock{ m_lock };
		m_tokens[userId] = token;
	}

	bool CharacterManager::IsValidUser(UserId userId, const std::string& token)
	{
		std::shared_lock<std::shared_mutex> lock{ m_lock };
		if (const auto found = m_tokens.find(userId);
			found != m_tokens.end())
		{
			if (found->second == token)
				return true;
		}
		return false;
	}

	auto CharacterManager::_Get(CharacterId id) -> std::shared_ptr<Character>
	{
		if (const auto found = m_characters.find(id);
			found != m_characters.end())
			return found->second;

		return nullptr;
	}
}