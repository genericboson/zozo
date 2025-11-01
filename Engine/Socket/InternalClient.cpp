#include "PCH.h"

#include "BoostTcpSocket.h"
#include "InternalClient.h"

namespace GenericBoson
{
	InternalClient::InternalClient(
		const std::shared_ptr<ServerBase>& pOwner,
		const std::string&                 ip,
		const std::string&                 port)
		: m_wpOwner(pOwner), m_ip(ip), m_port(port)
	{
	}

	asio::awaitable<bool> InternalClient::Initialize(const std::unique_ptr<IActor>& pActor)
	{
		NULL_CO_RETURN(pActor)

		const auto pOwner = m_wpOwner.lock();
		if (!pOwner)
			return;

		m_pSocket->Initialize(pActor);

		m_pSocket = std::make_shared<BoostTcpSocket>(
			ip::tcp::socket{ m_ioContext });

		co_await m_pSocket->ConnectAsync(m_ip, m_port,
			[this]() -> awaitable<void>
			{
				asio::co_spawn(co_await asio::this_coro::executor, [this]()
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
					}, asio::detached);

				asio::co_spawn(co_await asio::this_coro::executor, [this]()
					{
						while (true)
						{
							const auto pOwner = m_wpOwner.lock();
							if (!pOwner)
								break;

							if (!pOwner->IsRunning())
								break;

							co_await m_pSocket->Read();
						}
					}, asio::detached);
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