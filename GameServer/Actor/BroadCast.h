#pragma once

#include "MessageSchema/Common/Type_generated.h"

namespace GenericBoson
{
	class Character;

	class BroadCast
	{
	public:
		int64_t    senderCharacterId;

		virtual void Cast(const std::shared_ptr<Character>& pCharacter) const = 0;
	};

	class PositionCast : public BroadCast
	{
	public:
		Zozo::Vector2F  position;
		Zozo::Direction direction;
		bool            isMoved = false;

		void Cast(const std::shared_ptr<Character>& pCharacter) const override;
	};
}