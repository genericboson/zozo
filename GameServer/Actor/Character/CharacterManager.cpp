#include "PCH.h"

#include "Character.h"
#include "CharacterManager.h"

namespace GenericBoson
{
	void CharacterManager::AddCharacter(std::shared_ptr<Character>&& pCharacter)
	{
		m_characters[CharacterId{ pCharacter->Id() }] = pCharacter;
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

	bool CharacterManager::Initialize()
	{
		//auto queryStr = mysql::with_params(
		//	"SELECT name, level FROM zozo_game.character WHERE id = {};", characterId);

		//// #todo change to CharacterSelect_Select_UserCharacter
		//mysql::static_results<mysql::pfr_by_name<CharacterList_Select_UserCharacter>> result;
		//if (auto [dbErr] = co_await pServer->m_pDbConn->async_execute(
		//	queryStr,
		//	result,
		//	asio::as_tuple(asio::use_awaitable));
		//	dbErr)
		//{
		//	ERROR_LOG("Query execute error. error code - {}({})", dbErr.value(), dbErr.message());
		//	co_return;
		//}

		//auto selectResults = result.rows<0>();
		//if (selectResults.size() <= 0)
		//{
		//	WARN_LOG("[CharacterSelectReq] NoData. token : {}, user id : {}", tokenStr, userId);
		//	const auto ack = Zozo::CreateCharacterSelectAck(fbb, Zozo::ResultCode_NoData);
		//	const auto msg = Zozo::CreateGameMessage(fbb, Zozo::GamePayload_CharacterSelectAck, ack.Union());
		//	fbb.Finish(msg);
		//	co_return;
		//}

		//for (auto& selectResult : selectResults)
		//{
		//}

		return true;
	}

	auto CharacterManager::_Get(CharacterId id) -> std::shared_ptr<Character>
	{
		if (const auto found = m_characters.find(id);
			found != m_characters.end())
			return found->second;

		return nullptr;
	}
}