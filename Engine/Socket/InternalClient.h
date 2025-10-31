#pragma once

namespace GenericBoson
{
	class ServerBase;

	namespace asio = boost::asio;

	class InternalClient
	{
	public:
		InteranlClient(
			const ServerBase&  owner, 
			const std::string& ip, 
			const std::string& port);

		asio::awaitable<bool> Initialize();
		
	private:
		ServerBase& m_owner;

		std::string m_ip, m_port;
	};
}
