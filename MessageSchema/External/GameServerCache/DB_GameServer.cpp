#include "PCH.h"

#include "DB_GameServer.h"

namespace GenericBoson::Zozo
{
    CharacterCache::CharacterCache()
    {
        m_fields[ID] = std::make_shared<Id>(*this);
        m_fields[USER_ID] = std::make_shared<UserId>(*this);
        m_fields[NAME] = std::make_shared<Name>(*this);
        m_fields[LEVEL] = std::make_shared<Level>(*this);
    };

    CharacterCache::Id::Id(CharacterCache& owner)
        : m_owner(owner)
    {
    }

    void CharacterCache::Id::Set(const int64_t& param)
    {
        m_owner.CharacterT::id = param;
        m_flag = true;
    }

    auto CharacterCache::Id::Get() const
        -> const int64_t&
    {
        return m_owner.CharacterT::id;
    }

    auto CharacterCache::Id::GetName() const
        -> std::string
    {
        return "id";
    }

    bool CharacterCache::Id::IsFlagged() const
    {
        return m_flag;
    };

    CharacterCache::UserId::UserId(CharacterCache& owner)
        : m_owner(owner)
    {
    }

    void CharacterCache::UserId::Set(const int64_t& param)
    {
        m_owner.CharacterT::user_id = param;
        m_flag = true;
    }

    auto CharacterCache::UserId::Get() const
        -> const int64_t&
    {
        return m_owner.CharacterT::user_id;
    }

    auto CharacterCache::UserId::GetName() const
        -> std::string
    {
        return "user_id";
    }

    bool CharacterCache::UserId::IsFlagged() const
    {
        return m_flag;
    };

    CharacterCache::Name::Name(CharacterCache& owner)
        : m_owner(owner)
    {
    }

    void CharacterCache::Name::Set(const std::string& param)
    {
        m_owner.CharacterT::name = param;
        m_flag = true;
    }

    auto CharacterCache::Name::Get() const
        -> const std::string&
    {
        return m_owner.CharacterT::name;
    }

    auto CharacterCache::Name::GetName() const
        -> std::string
    {
        return "name";
    }

    bool CharacterCache::Name::IsFlagged() const
    {
        return m_flag;
    };

    CharacterCache::Level::Level(CharacterCache& owner)
        : m_owner(owner)
    {
    }

    void CharacterCache::Level::Set(const int32_t& param)
    {
        m_owner.CharacterT::level = param;
        m_flag = true;
    }

    auto CharacterCache::Level::Get() const
        -> const int32_t&
    {
        return m_owner.CharacterT::level;
    }

    auto CharacterCache::Level::GetName() const
        -> std::string
    {
        return "level";
    }

    bool CharacterCache::Level::IsFlagged() const
    {
        return m_flag;
    };

    auto CharacterCache::GetFieldNames() -> const std::vector<std::string>&
    {
        return m_names;
    };

    auto CharacterCache::GetObjectName() -> std::string
    {
        return "Character";
    };

}
