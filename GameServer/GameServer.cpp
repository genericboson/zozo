#include "PCH.h"

#include <filesystem>

#include <flatbuffers/flatbuffers.h>
#include <Engine/Socket/BoostTcpSocket.h>

#include "Actor/Character/Character.h"
#include "Actor/Character/CharacterManager.h"
#include "Actor/ZoneManager.h"
#include "GameServer.h"

#include <boost/json.hpp>
#include <MessageSchema/Internal/LobbyGame_generated.h>

namespace GenericBoson
{
	GameServer::GameServer(int32_t port /*= 8001*/)
		: ServerBase(port), m_pLobbyProxy{ std::make_shared<LobbyProxy>( *this ) }
	{
	}

	bool GameServer::ReadStaticData(const std::filesystem::path& path)
	{
		std::ifstream ifs(path.string());
		if (!ifs.is_open())
		{
			ERROR_LOG("Failed to open {}", path.string());
			return false;
		}

		boost::json::stream_parser parser;
		std::string line;
		while (std::getline(ifs, line))
		{
			parser.write(line);
		}
		parser.finish();

		boost::json::value jsonValue = parser.release();

		bool isFirst = true;
		int64_t classId = 0;
		for (const auto element : jsonValue.as_array())
		{
			const auto& obj = element.as_object();

			if (isFirst)
			{
				isFirst = false;

				if (const auto found = obj.find("CLASS_ID");found == obj.end())
				{
					classId = found->value().as_int64();
				}
				else
				{
					WARN_LOG("No CLASS_ID in static data file {}", path.string());
				}

				continue;
			}

			auto& staticData = StaticDataManager::GetInstance()->CreateStaticData(classId);
			CHECK_NULL();
			staticData->Insert( obj );
			//m_zones.emplace(zoneId, Zone{ zoneId, name });
		}
	}

	bool GameServer::ReadAllStaticData()
	{
		namespace fs = std::filesystem;

		fs::directory_iterator dirIter("StaticData");

		for (const auto& entry : dirIter )
		{
			if (entry.is_regular_file() && entry.path().extension() == ".json")
			{
				ReadStaticData(entry.path());
			}
		}

		return true;
	}

	bool GameServer::AfterReadIni()
	{
		if (!ReadAllStaticData())
		{
			return false;
		}

		m_pClient = std::make_unique<InternalClient>(shared_from_this(), m_lobbyIp, m_lobbyPort);
		m_pClient->SetOnConnected([this]() {
			flatbuffers::FlatBufferBuilder fbb;

			auto req = Zozo::CreateRegisterReq(fbb, m_id);
			auto msg = Zozo::CreateLobbyGameMessage(fbb,
				Zozo::LobbyGamePayload::LobbyGamePayload_RegisterReq,
				req.Union());

			fbb.Finish(msg);

			m_pClient->EnqueueMessage(fbb.GetBufferPointer(), fbb.GetSize());

			INFO_LOG("RegisterReq sent");
		});

		const auto clientTask = [this]() -> asio::awaitable<void>
			{
				co_await m_pClient->KeepSending(m_pLobbyProxy);
			};

		asio::co_spawn(m_ioContext, clientTask, asio::detached);

		return true;
	}

	bool GameServer::Start()
	{
		if (!ServerBase::Start())
		{
			ERROR_LOG("ServerBase::Start for GameServer failed");
			return false;
		}

		return true;
	}

	asio::awaitable<void> GameServer::InitializeSingletons()
	{
		if (!co_await ZoneManager::GetInstance()->Initialize())
		{
			ERROR_LOG("ZoneManager initilize failed");
			co_return;
		}

		co_return;
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

		return opIniPt;
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