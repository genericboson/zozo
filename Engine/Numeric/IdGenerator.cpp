#include "PCH.h"

#include "IdGenerator.h"

namespace GenericBoson
{
	//2 ^ 42 = 4,398,046,511,104
	//// time stamp ( max = 2109년 May 15일 Wednesday AM 7:35:11.104 )

	//2 ^ 16 = 65, 535
	//// server id

	//2 ^ 6 = 64
	//// atomic count

	int64_t IdGenerator::CreateId(const uint16_t serverId)
	{
		uint64_t timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()).count();

		timestamp << 16;

		timestamp |= serverId;

		timestamp << 3;

		static std::atomic_uint64_t count{ 0 };
		decltype(count) copiedCount = ++count;

		uint8_t tmpByte = copiedCount % std::numeric_limits<uint8_t>::max();

		timestamp |= tmpByte;

		return timestamp;
	}
}