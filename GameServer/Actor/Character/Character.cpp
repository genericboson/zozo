#include "PCH.h"

#include <memory>

#include <boost/asio.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/mysql.hpp>
#include <boost/mysql/static_results.hpp>
#include <boost/mysql/pfr.hpp>

#include <flatbuffers/flatbuffers.h>

#include <Engine/EnvironmentVariable.h>
#include <Engine/Numeric/IdGenerator.h>
#include <Engine/Socket/ISocket.h>
#include <Engine/Socket/BoostTcpSocket.h>
#include <Engine/Util/StopWatch.h>

#include <MessageSchema/Common/Type_generated.h>
#include <MessageSchema/External/GameServer_generated.h>

#include "GameServer.h"
#include "Character.h"
#include "CharacterManager.h"
#include "StaticResults.h"

namespace GenericBoson
{
    namespace mysql = boost::mysql;

    Character::Character(
        const std::shared_ptr<GameServer>& pServer,
        const std::shared_ptr<ISocket>&    pSocket)
		: m_id(0), m_server(*pServer), m_pSocket(pSocket),
		m_strand(asio::make_strand(pServer->GetIoContextRef()))
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

		CharacterManager::GetInstance()->AddUnselected(shared_from_this());

        return true;
    }

    asio::awaitable<void> Character::Update()
    {
        co_return co_await ConsumeAll();
    }

    void Character::Write(const uint8_t* pData, const std::size_t size)
    {
        m_pSocket->EnqueueMessage(pData, size);
    }

    void Character::OnDisconnected()
    {
        CharacterManager::GetInstance()->RemoveCharacter(shared_from_this());
    }

    void Character::OnAccepted()
    {
        INFO_LOG("Client accepted ( temporary id - {} )", m_id);
    }

    int64_t Character::GetUpdatePeriodMs() const
    {
        return Environment::GetCharacterUpdatePeriodMs();
    }

    asio::awaitable<void> Character::Read(const uint8_t* pData, std::size_t dataSize)
    {
        using namespace Zozo;

        auto verifier = flatbuffers::Verifier(pData, dataSize);
        if (!VerifyGameMessageBuffer(verifier))
            co_return;

        auto message = Zozo::GetGameMessage(pData);
        NULL_CO_VOID_RETURN(message);

        switch (message->payload_type())
        {
        case GamePayload::GamePayload_CharacterListReq:
			co_await RecvCharacterListReq(message);
            break;
        case GamePayload::GamePayload_CharacterSelectReq:
            co_await RecvCharacterSelectReq(message);
            break;
        case GamePayload::GamePayload_CharacterSelectAck:
            {
                ERROR_LOG("Logic error");
            }
            break;
        case GamePayload::GamePayload_CharacterPositionUpdateReq:
			RecvCharacterPositionUpdateReq(message);
            break;
        case GamePayload::GamePayload_CharacterPositionUpdateAck:
            {
			    ERROR_LOG("Logic error");
            }
            break;
        case GamePayload::GamePayload_CharacterCreateReq:
            {
                m_id = GenericBoson::IdGenerator::CreateId(m_server.m_id);
            }
            break;
        case GamePayload::GamePayload_CharacterCreateAck:
            {
                ERROR_LOG("Logic error");
            }
            break;
        default:
            WARN_LOG("Unhandled message ( payload_type - {} )", 
                EnumNameGamePayload(message->payload_type()));
			break;
        }
    }

    asio::strand<asio::io_context::executor_type> Character::GetStrand() const
    {
        return m_strand;
    }
}
