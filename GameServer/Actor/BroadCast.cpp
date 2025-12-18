#include "PCH.h"

#include "BroadCast.h"
#include "Character/Character.h"

#include "MessageSchema/External/CharacterPositionUpdate_generated.h"

namespace GenericBoson
{
	void PositionCast::Cast(const std::shared_ptr<Character>& pCharacter)
	{
		flatbuffers::FlatBufferBuilder fbb;

		const auto req = Zozo::CreateCharacterPositionUpdateReq(
			fbb,
			&position);

		fbb.Finish(req);

		pCharacter->Write(fbb.GetBufferPointer(), fbb.GetSize());
	}
}