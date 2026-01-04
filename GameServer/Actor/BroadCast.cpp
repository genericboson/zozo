#include "PCH.h"

#include <MessageSchema/External/GameServer_generated.h>

#include "BroadCast.h"
#include "Character/Character.h"

namespace GenericBoson
{
	void PositionCast::Cast(const std::shared_ptr<Character>& pCharacter) const
	{
		flatbuffers::FlatBufferBuilder fbb;

		const auto req = Zozo::CreateCharacterPositionUpdateReq(
			fbb,
			pCharacter->Id(),
			direction,
			isMoved,
			&position);

		const auto msg = Zozo::CreateGameMessage(fbb,
			Zozo::GamePayload_CharacterPositionUpdateReq,
			req.Union());

		fbb.Finish(msg);

		pCharacter->Write(fbb.GetBufferPointer(), fbb.GetSize());
	}
}