#include "PCH.h"

#include "DBCacheClient.h"

#include <MessageSchema/Internal/DBCacheLobby_generated.h>

namespace GenericBoson
{
	auto DBCacheClient::Upsert(const flatbuffers::String& accountStr, const flatbuffers::String& passwordStr)
		-> boost::future<std::shared_ptr<flatbuffers::FlatBufferBuilder>>
	{
		flatbuffers::FlatBufferBuilder fbb;
		//auto account = fbb.CreateString(account);
		//auto password = fbb.CreateString(password);
		auto loginDBReq = Zozo::CreateLoginDBReq(fbb);// , account, password);
		auto lobbyMsg = Zozo::CreateDBCacheLobbyMessage(fbb, 
			Zozo::DBCacheLobbyPayload::DBCacheLobbyPayload_LoginDBReq, 
			loginDBReq.Union());

		fbb.Finish(lobbyMsg);

		// db job...

		std::string accountTest(accountStr.c_str());
		std::string passwordTest(passwordStr.c_str());

		boost::promise<std::shared_ptr<flatbuffers::FlatBufferBuilder>> promise;

		//promise.set_value(pFbb);

		return promise.get_future();
	}
}