#include "PCH.h"

#include "BroadCast.h"
#include "Character/Character.h"

namespace GenericBoson
{
	void PositionCast::Cast(const std::shared_ptr<Character>& pCharacter)
	{
		flatbuffers::FlatBufferBuilder fbb;

		

		pCharacter->Write();
	}
}