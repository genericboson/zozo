#pragma once

#include <Engine/Singleton.h>

namespace GenericBoson
{
	class DBClient;

	class DBClientManager : public Singleton< DBClientManager >
	{
	public:
		void AddDBClient(std::shared_ptr< DBClient >&& pLobbyUser);

	private:
		std::unordered_map< int64_t, std::shared_ptr< DBClient > > m_dbClients;
	};
}