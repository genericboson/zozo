#include "PCH.h"

#include "DB_GameServer.h"

namespace GenericBoson::Zozo
{
    CharacterCache::CharacterCache()
    {
        m_fields[ID] = std::make_shared<Id>(*this);
        m_fields[USER_ID] = std::make_shared<User_id>(*this);
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

    bool CharacterCache::Id::IsFlagged() const
    {
        return m_flag;
    };

    CharacterCache::User_id::User_id(CharacterCache& owner)
        : m_owner(owner)
    {
    }

    void CharacterCache::User_id::Set(const int64_t& param)
    {
        m_owner.CharacterT::user_id = param;
        m_flag = true;
    }

    auto CharacterCache::User_id::Get() const
        -> const int64_t&
    {
        return m_owner.CharacterT::user_id;
    }

    bool CharacterCache::User_id::IsFlagged() const
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
