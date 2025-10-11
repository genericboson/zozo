#include "PCH.h"

#include "DBCacheClient.h"

#include <Engine/Socket/BoostTcpSocket.h>
#include <MessageSchema/Internal/DBCache_generated.h>

namespace GenericBoson
{
	DBCacheClient::DBCacheClient(
		const std::string&           ip, 
		const std::string&           port,
		std::shared_ptr<ServerBase>& pOwner)
		: m_ip(ip), m_port(port), m_wpOwner(pOwner)
	{
	}

	void DBCacheClient::Initialize()
	{
		const auto pOwner = m_wpOwner.lock();
		if (!pOwner)
			return;

		m_pSocket = std::make_shared<BoostTcpSocket>(
			ip::tcp::socket{ m_ioContext });

		m_pSocket->ConnectAsync(m_ip, m_port,
			[this]() -> awaitable<void>
			{
				while (true)
				{
					const auto pOwner = m_wpOwner.lock();
					if (!pOwner)
						break;

					if (!pOwner->IsRunning())
						break;

					co_await m_pSocket->Write();
				}
			});
	}

	auto DBCacheClient::Upsert(const flatbuffers::String& accountStr)
		-> boost::future<std::shared_ptr<flatbuffers::FlatBufferBuilder>>
	{
		flatbuffers::FlatBufferBuilder fbb;
		auto loginDBReq = Zozo::CreateLoginDBReq(fbb);// , account, password);
		auto dbcacheMsg = Zozo::CreateDBCacheLobbyMessage(fbb, 
			Zozo::DBCacheLobbyPayload::DBCacheLobbyPayload_LoginDBReq, 
			loginDBReq.Union());

		fbb.Finish(dbcacheMsg);

		m_pSocket->EnqueueMessage(fbb.GetBufferPointer(), fbb.GetSize());

		// db job...

		std::string accountTest(accountStr.c_str());

		boost::promise<std::shared_ptr<flatbuffers::FlatBufferBuilder>> promise;

		//promise.set_value(pFbb);

		return promise.get_future();
	}
}