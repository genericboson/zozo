#pragma once

namespace GenericBoson
{
	class BroadCast
	{
		int64_t    senderCharacterId;

		void Cast() = 0;
	};

	class PositionCast : public BroadCast
	{
		int32_t    x, y;

		void Cast()
		{

		}
	};
}