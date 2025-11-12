#include "PCH.h"

#include <flatbuffers/flatbuffers.h>
#include <Engine/Socket/BoostTcpSocket.h>

#include "Actor/Character/Character.h"
#include "Actor/Character/CharacterManager.h"
#include "GameServer.h"

#include <MessageSchema/Internal/LobbyGame_generated.h>

namespace GenericBoson
{
	GameServer::GameServer(int32_t port /*= 8001*/)
		: ServerBase(port)
	{
	}

	bool GameServer::Start()
	{
		if (!ServerBase::Start())
		{
			ERROR_LOG("ServerBase::Start for GameServer failed");
			return false;
		}

		OnAfterReadIni = [this](){
			m_pClient = std::make_unique<InternalClient>(shared_from_this(), m_lobbyIp, m_lobbyPort);
			m_pClient->SetOnConnected([this]() {
				flatbuffers::FlatBufferBuilder fbb;

				auto req = Zozo::CreateRegisterReq(fbb, m_id);
				auto msg = Zozo::CreateLobbyGameMessage(fbb,
					Zozo::LobbyGamePayload::LobbyGamePayload_RegisterReq,
					req.Union());

				fbb.Finish(msg);

				m_pClient->EnqueueMessage(fbb.GetBufferPointer(), fbb.GetSize());
				});

			const auto clientTask = [this]() -> asio::awaitable<void>
				{
					co_await m_pClient->KeepSending(m_pLobbyProxy);
				};

			asio::co_spawn(m_ioContext, clientTask, asio::detached);

			INFO_LOG("GameServer started ( port - {} )", m_listeningPort);
		};

		return true;
	}

	std::optional<pt::ptree> GameServer::ReadIni()
	{
		const auto opIniPt = ServerBase::ReadIni();
		if (!opIniPt)
			return opIniPt;

		try
		{
			m_id = opIniPt->get<decltype(m_id)>("SERVER_ID");
		}
		catch (const boost::wrapexcept<boost::property_tree::ptree_bad_path>& e)
		{
			ERROR_LOG("No SERVER_ID in INI file");
			return std::nullopt;
		}

		m_lobbyIp   = opIniPt->get<decltype(m_lobbyIp)>("LOBBY_IP", "127.0.0.1");
		m_lobbyPort = opIniPt->get<decltype(m_lobbyPort)>("LOBBY_PORT", "8002");
	}

	auto GameServer::CreateActor(const std::shared_ptr<ISocket>& pSocket) 
		-> std::shared_ptr<IActor>
	{
		return std::make_shared<Character>(shared_from_this(), pSocket);
	}

	auto GameServer::CreateGameServer(int32_t port /*= 8001*/) -> std::shared_ptr<GameServer>
	{
		return std::make_shared<GameServer>(port);
	}
}