#pragma once

namespace GenericBoson
{
	class Character;

	class BroadCast
	{
	public:
		int64_t    senderCharacterId;

		virtual void Cast(const std::shared_ptr<Character>& pCharacter) = 0;
	};

	class PositionCast : public BroadCast
	{
	public:
		int32_t    x, y;

		void Cast(const std::shared_ptr<Character>& pCharacter) override;
	};
}