#include "PCH.h"

#include <boost/mysql.hpp>
#include <boost/mysql/static_results.hpp>
#include <boost/mysql/pfr.hpp>

#include <format>

#include <Engine/Tx/MemObject.h>
#include <Engine/Tx/MemTx.h>
#include <Engine/Tx/Continuation.h>
#include <Engine/Tx/CustomAttributes.h>
#include <MessageSchema/External/GameServerMem/DB_GameServer.h>
#include <MessageSchema/External/GameServer_generated.h>

#include "Actor/Character/Character.h"
#include "Actor/Character/CharacterManager.h"
#include "GameServer.h"
#include "StaticResults.h"

namespace GenericBoson
{
    namespace mysql = boost::mysql;

    asio::awaitable<void> Character::RecvTryGetItemReq(const Zozo::GameMessage* message)
    {
    }
}
