#include "PCH.h"

#include <memory>

#include <boost/asio.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/mysql.hpp>
#include <boost/mysql/static_results.hpp>
#include <boost/mysql/pfr.hpp>

#include <flatbuffers/flatbuffers.h>

#include <Engine/Socket/ISocket.h>
#include <Engine/Socket/BoostTcpSocket.h>

#include <MessageSchema/External/GameServer_generated.h>

#include "Character.h"
#include "CharacterManager.h"
#include "StaticResults.h"

namespace GenericBoson
{
    Character::Character(const std::shared_ptr<ISocket>& pSocket)
		: m_id(0), m_pSocket(pSocket)
    {
    }

    int64_t Character::Id() const
    {
        return m_id;
    }

    bool Character::Initialize()
    {
        if (!m_pSocket->IsValid())
            return false;

        CharacterManager::GetInstance()->AddCharacter(shared_from_this());
        return true;
    }

    void Character::Write()
    {
    }

    void Character::OnDisconnected()
    {
    }

    void Character::OnAccepted()
    {
        INFO_LOG("Client accepted ( ClientId - {} )", m_id);
    }

    asio::awaitable<void> Character::Read(const uint8_t* pData, std::size_t dataSize)
    {
        using namespace Zozo;

        auto verifier = flatbuffers::Verifier(pData, dataSize);
        if (!VerifyGameMessageBuffer(verifier))
            co_return;

        auto message = Zozo::GetGameMessage(pData);
        NULL_CO_RETURN(message)

        flatbuffers::FlatBufferBuilder fbb;
        
        switch (message->payload_type())
        {
        case GamePayload::GamePayload_CharacterListReq:
            {
                auto req = message->payload_as_CharacterListReq();
                NULL_CO_RETURN(req)

                    const auto accountStr = req->account()->c_str();
                const auto tokenStr = req->token()->c_str();

                INFO_LOG("[CharacterListReq] token : {}", tokenStr);

                auto queryStr = mysql::with_params(
                    "SELECT uc.name AS name, uc.level AS level "
                    "FROM zozo_lobby.user JOIN zozo_lobby.user_character AS uc "
                    "ON user.id = uc.user_id "
                    "WHERE user.account = {} AND user.token = {};",
                    accountStr, tokenStr);

                mysql::static_results<mysql::pfr_by_name<CharacterList_Select_UserCharacter>> result;
                if (auto [dbErr] = co_await m_server.m_pDbConn->async_execute(
                    queryStr,
                    result,
                    asio::as_tuple(asio::use_awaitable));
                    dbErr)
                {
                    ERROR_LOG("Query execute error. error code - {}({})", dbErr.value(), dbErr.message());
                    co_return;
                }

                auto selectResults = result.rows<0>();

                std::vector<flatbuffers::Offset<flatbuffers::String>> names;

                for (auto& selectResult : selectResults)
                {
                    auto name = fbb.CreateString(std::format("{} [Lv.{}]",
                        selectResult.name.value_or(""),
                        selectResult.level.value_or(0)));
                    names.emplace_back(std::move(name));
                }

                const auto namesOffset = fbb.CreateVector(names);

                const auto ack = Zozo::CreateCharacterListAck(fbb, Zozo::ResultCode_Success, namesOffset);
                const auto msg = Zozo::CreateGameMessage(fbb, Zozo::GamePayload_CharacterListAck, ack.Union());

                fbb.Finish(msg);
            }
        case GamePayload::GamePayload_CharacterMoveReq:
            {
			    auto moveReq = message->payload_as_CharacterMoveReq();
                INFO_LOG("CharacterPos:{},{}", moveReq->x(), moveReq->y());
            }
            break;
        case GamePayload::GamePayload_CharacterMoveAck:
            {
			    ERROR_LOG("Logic error");
            }
            break;
        default:
            WARN_LOG("Unhandled message ( payload_type - %s )", 
                EnumNameGamePayload(message->payload_type()));
			break;
        }

        m_pSocket->EnqueueMessage(fbb.GetBufferPointer(), fbb.GetSize());
    }
}
