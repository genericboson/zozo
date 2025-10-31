#include "PCH.h"

#include "BoostTcpSocket.h"
#include "InternalClient.h"

namespace GenericBoson
{
	InternalClient::InternalClient(
		const ServerBase&  owner,
		const std::string& ip,
		const std::string& port)
		: m_owner(owner), m_ip(ip), m_port(port)
	{
	}

	asio::awaitable<bool> InternalClient::Initialize()
	{
		const auto pOwner = m_wpOwner.lock();
		if (!pOwner)
			return;

		m_pSocket = std::make_shared<BoostTcpSocket>(
			ip::tcp::socket{ m_ioContext });

		co_await m_pSocket->ConnectAsync(m_ip, m_port,
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

	//auto DBCacheClient::Upsert(const flatbuffers::String& accountStr)
	//	-> boost::future<std::shared_ptr<flatbuffers::FlatBufferBuilder>>
	//{
	//	flatbuffers::FlatBufferBuilder fbb;
	//	auto loginDBReq = Zozo::CreateLoginDBReq(fbb);// , account, password);
	//	auto dbcacheMsg = Zozo::CreateDBCacheLobbyMessage(fbb,
	//		Zozo::DBCacheLobbyPayload::DBCacheLobbyPayload_LoginDBReq,
	//		loginDBReq.Union());

	//	fbb.Finish(dbcacheMsg);

	//	m_pSocket->EnqueueMessage(fbb.GetBufferPointer(), fbb.GetSize());
	//}
}