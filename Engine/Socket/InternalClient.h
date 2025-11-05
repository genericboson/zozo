#pragma once

#include "BoostTcpSocket.h"

namespace GenericBoson
{
	class BoostTcpSocket;
	class IActor;
	class ServerBase;

	namespace asio = boost::asio;

	class InternalClient
	{
	public:
		InternalClient(
			const std::shared_ptr<ServerBase>&  pOwner, 
			const std::string&                  ip, 
			const std::string&                  port);

		asio::awaitable<bool> Initialize(const std::shared_ptr<IActor>& pActor);
		
	private:
		std::weak_ptr<ServerBase>       m_wpOwner;
		std::unique_ptr<BoostTcpSocket> m_pSocket;

		std::string                     m_ip, m_port;
	};
}
