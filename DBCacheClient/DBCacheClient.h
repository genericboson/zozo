#pragma once

#include <boost/asio.hpp>

#include <flatbuffers/flatbuffers.h>

#include <Engine/Singleton.h>
#include <Engine/Tx/Continuation.h>
#include <Engine/Socket/ServerBase.h>
#include <Engine/Socket/ISocket.h>

namespace GenericBoson
{
	namespace Zozo { struct DBCacheLobbyMessage; }

	using namespace boost::asio;

	class DBCacheClient : public Singleton<DBCacheClient>
	{
	public:
		DBCacheClient(
			const std::string&           ip,
			const std::string&           port,
			std::shared_ptr<ServerBase>& pOwner);
		virtual ~DBCacheClient() = default;

		void Initialize();

		auto Upsert(const flatbuffers::String& accountStr)
			-> boost::future<std::shared_ptr<flatbuffers::FlatBufferBuilder>>;
	private:
		io_context                 m_ioContext;
		std::shared_ptr<ISocket>   m_pSocket;
		std::weak_ptr<ServerBase>  m_wpOwner;

		std::string                m_ip, m_port;
	};
}