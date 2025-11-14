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

	LobbyProxy::LobbyProxy(GameServer& server) :
		m_server(server)
	{

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

				NULL_CO_RETURN(registerAck->db_ip());
				NULL_CO_RETURN(registerAck->db_acount());
				NULL_CO_RETURN(registerAck->db_password());
				NULL_CO_RETURN(registerAck->db_main_schema());
				NULL_CO_RETURN(registerAck->db_port());

				NULL_CO_RETURN(registerAck->server_name());
				NULL_CO_RETURN(registerAck->listen_port());
				NULL_CO_RETURN(registerAck->db_ip());

				m_server.m_dbIp          = registerAck->db_ip()->str();
				m_server.m_dbAccount     = registerAck->db_acount()->str();
				m_server.m_dbPassword    = registerAck->db_password()->str();
				m_server.m_dbMainSchema  = registerAck->db_main_schema()->str();
				m_server.m_dbPort        = registerAck->db_port();

				m_server.m_name          = registerAck->server_name()->str();
				m_server.m_listeningPort = registerAck->listen_port();
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