#include "PCH.h"

#include <flatbuffers/flatbuffers.h>

#include "LobbyProxy.h"

#include <MessageSchema/Internal/LobbyGame_generated.h>

namespace GenericBoson
{
	int64_t LobbyProxy::Id() const
	{
		return 0;
	}
	void LobbyProxy::OnDisconnected()
	{
	}
	void LobbyProxy::OnAccepted()
	{
	}
	bool LobbyProxy::Initialize()
	{
		return false;
	}

	asio::awaitable<void> LobbyProxy::Read(const uint8_t* pData, std::size_t dataSize)
	{
		using namespace Zozo;

		auto verifier = flatbuffers::Verifier(pData, dataSize);
		if (!VerifyLobbyGameMessageBuffer(verifier))
			co_return;

		auto message = Zozo::GetLobbyGameMessage(pData);
		NULL_CO_RETURN(message)

			flatbuffers::FlatBufferBuilder fbb;

		switch (message->payload_type())
		{
		case LobbyGamePayload::LobbyGamePayload_RegisterAck:
			{
				auto registerAck = message->payload_as_RegisterAck();
				NULL_CO_RETURN(registerAck);
			}
            break;
		case LobbyGamePayload::LobbyGamePayload_RegisterReq:
			{
				ERROR_LOG("Logic error");
			}
			break;
        default:
            {
            }
            break;
        }
	}
}