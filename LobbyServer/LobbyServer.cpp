#include "PCH.h"

#include <Engine/EnvironmentVariable.h>
#include <Engine/Socket/BoostTcpSocket.h>

#include "LobbyServer.h"

#include "Session/LobbyStub.h"
#include "Session/LobbyUser.h"
#include "Session/LobbyUserManager.h"

namespace GenericBoson
{
	LobbyServer::LobbyServer(ELobbyServerSort sort, int32_t port /*= 0*/)
		: ServerBase(port), m_sort(sort)
	{
	}

	auto LobbyServer::CreateActor(const std::shared_ptr<ISocket>& pSocket)
		-> std::shared_ptr<IActor>
	{
		assert(m_sort != ELobbyServerSort::NONE);

		if ( m_sort == ELobbyServerSort::EXTERNAL )
			return std::make_shared<LobbyUser>(*this, pSocket);

		return std::make_shared<LobbyStub>(*this, pSocket);
	}

	bool LobbyServer::Start()
	{
		auto startResult = ServerBase::Start();

		if (m_sort == ELobbyServerSort::EXTERNAL)
		{
			INFO_LOG("External LobbyServer started ( port - {} )", m_listeningPort);
		}
		else
		{
			INFO_LOG("Internal LobbyServer started ( port - {} )", m_listeningPort);
		}

		return startResult;
	}

	std::optional<pt::ptree> LobbyServer::ReadIni()
	{
		auto opIniPt = ServerBase::ReadIni();
		if (!opIniPt)
			return std::nullopt;

		const auto& iniPt = *opIniPt;

		Environment::SetDBHost(iniPt.get<std::string>("DB_IP", "127.0.0.1"));
		Environment::SetDBPort(iniPt.get<uint16_t>("DB_PORT", 3306));
		Environment::SetDBUser(iniPt.get<std::string>("DB_ACCOUNT", "root"));
		Environment::SetDBPassword(iniPt.get<std::string>("DB_PASSWORD", "1234"));
		Environment::SetDBName(iniPt.get<std::string>("DB_MAIN_SCHEMA"));

		if ( !m_listeningPort )
		{
			if (m_sort == ELobbyServerSort::EXTERNAL)
				m_listeningPort = iniPt.get<decltype(m_listeningPort)>("EXTERNAL_LISTEN_PORT");
			else if (m_sort == ELobbyServerSort::INTERNAL)
				m_listeningPort = iniPt.get<decltype(m_listeningPort)>("INTERNAL_LISTEN_PORT");
			else
				ERROR_LOG("LOGIC ERROR");
		}

		return opIniPt;
	}
}