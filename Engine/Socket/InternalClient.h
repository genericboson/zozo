#pragma once

namespace GenericBoson
{
	class ServerBase;

	namespace asio = boost::asio;

	class InternalClient
	{
	public:
		InternalClient(
			const std::shared_ptr<ServerBase>&  pOwner, 
			const std::string&                  ip, 
			const std::string&                  port);

		asio::awaitable<bool> Initialize(const std::unique_ptr<IActor>& pActor);
		
	private:
		std::weak_ptr<ServerBase> m_wpOwner;

		std::string               m_ip, m_port;
	};
}
