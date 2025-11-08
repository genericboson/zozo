#include "PCH.h"

#include "InternalClient.h"
#include "ServerBase.h"

namespace GenericBoson
{
	InternalClient::InternalClient(
		const std::shared_ptr<ServerBase>& pOwner,
		const std::string&                 ip,
		const std::string&                 port)
		: m_wpOwner(pOwner), m_ip(ip), m_port(port)
	{
	}

	void InternalClient::SetOnConnected(std::function<void()>&& onConnected)
	{
		m_onConnected = onConnected;
	}

	void InternalClient::EnqueueMessage(const uint8_t* buffer, size_t size)
	{
		m_pSocket->EnqueueMessage(buffer, size);
	}

	asio::awaitable<bool> InternalClient::KeepSending(const std::shared_ptr<IActor>& pActor)
	{
		NULL_CO_RETURN(pActor, false)

		const auto pOwner = m_wpOwner.lock();
		if (!pOwner)
			co_return false;

		m_pSocket = std::make_unique<BoostTcpSocket>(pOwner->GetIoContextRef());

		m_pSocket->Initialize(pActor);

		co_await m_pSocket->ConnectAsync(m_ip, m_port,
			[this]() -> asio::awaitable<void>
			{
				m_onConnected();

				asio::co_spawn(co_await asio::this_coro::executor,
					[this]() -> asio::awaitable<void>
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

				asio::co_spawn(co_await asio::this_coro::executor, 
					[this]() -> asio::awaitable<void>
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