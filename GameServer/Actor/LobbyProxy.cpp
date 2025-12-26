#include "PCH.h"

#include <flatbuffers/flatbuffers.h>

#include "LobbyProxy.h"
#include "Character/CharacterManager.h"

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
		NULL_CO_VOID_RETURN(message);

		switch (message->payload_type())
		{
		case LobbyGamePayload::LobbyGamePayload_RegisterAck:
			{
				auto registerAck = message->payload_as_RegisterAck();
				NULL_CO_VOID_RETURN(registerAck);

				INFO_LOG("RegisterAck received");

				NULL_CO_VOID_RETURN(registerAck->db_ip());
				NULL_CO_VOID_RETURN(registerAck->db_acount());
				NULL_CO_VOID_RETURN(registerAck->db_password());
				NULL_CO_VOID_RETURN(registerAck->db_main_schema());
				NULL_CO_VOID_RETURN(registerAck->db_port());

				NULL_CO_VOID_RETURN(registerAck->server_name());
				NULL_CO_VOID_RETURN(registerAck->listen_port());
				NULL_CO_VOID_RETURN(registerAck->db_ip());

				NULL_CO_VOID_RETURN(registerAck->server_id() == m_server.m_id);

				m_server.m_dbIp          = registerAck->db_ip()->str();
				m_server.m_dbAccount     = registerAck->db_acount()->str();
				m_server.m_dbPassword    = registerAck->db_password()->str();
				m_server.m_dbMainSchema  = registerAck->db_main_schema()->str();
				m_server.m_dbPort        = registerAck->db_port();

				m_server.m_name          = registerAck->server_name()->str();
				m_server.m_listeningPort = registerAck->listen_port();

				if (co_await m_server.InitializeConnection())
				{
					INFO_LOG("GameServer started ( port - {} )", m_server.m_listeningPort);

					m_server.InitializeSingletons();
				}
				else
				{
					WARN_LOG("GameServer failed ( port - {} )", m_server.m_listeningPort);
				}
			}
            break;
		case LobbyGamePayload::LobbyGamePayload_RegisterReq:
			{
				ERROR_LOG("Logic error");
			}
			break;
		case LobbyGamePayload::LobbyGamePayload_AuthRelayReq:
			{
				auto relayReq = message->payload_as_AuthRelayReq();
				NULL_CO_VOID_RETURN(relayReq);

				INFO_LOG("AuthRelayReq received. UserId - {}, Token - {}",
					relayReq->user_id(),
					relayReq->token()->c_str());

				CharacterManager::GetInstance()->RegiterToken(
					UserId{ relayReq->user_id() }, relayReq->token()->str());

				flatbuffers::FlatBufferBuilder fbb;

				auto ack = Zozo::CreateAuthRelayAck(fbb, Zozo::ResultCode_Success);
				auto msg = Zozo::CreateLobbyGameMessage(fbb, Zozo::LobbyGamePayload_AuthRelayAck, ack.Union());

				fbb.Finish(msg);

				m_server.m_pClient->EnqueueMessage(fbb.GetBufferPointer(), fbb.GetSize());
			}
			break;
		case LobbyGamePayload::LobbyGamePayload_AuthRelayAck:
			{
				ERROR_LOG("Logic error");
			}
			break;
        default:
            {
				ERROR_LOG("Invalid message sent to LobbyProxy. type - {}", 
					EnumNameLobbyGamePayload(message->payload_type()));
            }
            break;
        }
	}
}