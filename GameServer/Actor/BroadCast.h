#pragma once

namespace GenericBoson
{
	class Character;

	class BroadCast
	{
		int64_t    senderCharacterId;

		void Cast(const std::shared_ptr<Character>& pCharacter) = 0;
	};

	class PositionCast : public BroadCast
	{
		int32_t    x, y;

		void Cast(const std::shared_ptr<Character>& pCharacter) override;
	};
}