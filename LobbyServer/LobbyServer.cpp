#include "PCH.h"

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

		m_dbIp = iniPt.get<decltype(m_dbIp)>("DB_IP", "127.0.0.1");
		m_dbPort = iniPt.get<decltype(m_dbPort)>("DB_PORT", 3306);
		m_dbAccount = iniPt.get<decltype(m_dbAccount)>("DB_ACCOUNT", "root");
		m_dbPassword = iniPt.get<decltype(m_dbPassword)>("DB_PASSWORD", "1234");
		m_dbMainSchema = iniPt.get<decltype(m_dbMainSchema)>("DB_MAIN_SCHEMA");

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