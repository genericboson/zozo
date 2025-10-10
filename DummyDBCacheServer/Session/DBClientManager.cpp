#include "PCH.h"

#include "DBClient.h"
#include "DBClientManager.h"

namespace GenericBoson
{
	void DBClientManager::AddDBClient(std::shared_ptr<DBClient>&& pDBClient)
	{
		m_dbClients[pDBClient->Id()] = pDBClient;
	}
}