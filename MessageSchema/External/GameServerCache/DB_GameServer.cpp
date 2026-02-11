#include "PCH.h"

#include "DB_GameServer.h"

#include <Engine/Concepts.h>

namespace GenericBoson::Zozo
{
    CharacterCache::CharacterCache()
    {
        m_fields["id"] = std::make_shared<Id>(*this);
        m_pId = m_fields["id"].get();
        m_fields["user_id"] = std::make_shared<UserId>(*this);
        m_pUserId = m_fields["user_id"].get();
        m_fields["name"] = std::make_shared<Name>(*this);
        m_pName = m_fields["name"].get();
        m_fields["level"] = std::make_shared<Level>(*this);
        m_pLevel = m_fields["level"].get();
    };

    CharacterCache::Id::Id(CharacterCache& owner)
        : m_owner(owner)
    {
    }

    void CharacterCache::Id::Set(const int64_t& param)
    {
        m_owner.CharacterT::id = param;
        m_isBound = true;
    }

    auto CharacterCache::Id::Get() const
        -> const int64_t&
    {
        return m_owner.CharacterT::id;
    }

    std::string CharacterCache::Id::GetName() const
    {
        return "id";
    }

    std::string CharacterCache::Id::GetValueString() const
    {
        return std::to_string(m_owner.CharacterT::id);
    }

    bool CharacterCache::Id::IsBound() const
    {
        return m_isBound;
    };

    CharacterCache::Id& CharacterCache::GetId()
    {
        return *static_cast<CharacterCache::Id*>(m_pId);
    };

    CharacterCache::UserId::UserId(CharacterCache& owner)
        : m_owner(owner)
    {
    }

    void CharacterCache::UserId::Set(const int64_t& param)
    {
        m_owner.CharacterT::user_id = param;
        m_isBound = true;
    }

    auto CharacterCache::UserId::Get() const
        -> const int64_t&
    {
        return m_owner.CharacterT::user_id;
    }

    std::string CharacterCache::UserId::GetName() const
    {
        return "user_id";
    }

    std::string CharacterCache::UserId::GetValueString() const
    {
        return std::to_string(m_owner.CharacterT::user_id);
    }

    bool CharacterCache::UserId::IsBound() const
    {
        return m_isBound;
    };

    CharacterCache::UserId& CharacterCache::GetUserId()
    {
        return *static_cast<CharacterCache::UserId*>(m_pUserId);
    };

    CharacterCache::Name::Name(CharacterCache& owner)
        : m_owner(owner)
    {
    }

    void CharacterCache::Name::Set(const std::string& param)
    {
        m_owner.CharacterT::name = param;
        m_isBound = true;
    }

    auto CharacterCache::Name::Get() const
        -> const std::string&
    {
        return m_owner.CharacterT::name;
    }

    std::string CharacterCache::Name::GetName() const
    {
        return "name";
    }

    std::string CharacterCache::Name::GetValueString() const
    {
        return m_owner.CharacterT::name;
    }

    bool CharacterCache::Name::IsBound() const
    {
        return m_isBound;
    };

    CharacterCache::Name& CharacterCache::GetName()
    {
        return *static_cast<CharacterCache::Name*>(m_pName);
    };

    CharacterCache::Level::Level(CharacterCache& owner)
        : m_owner(owner)
    {
    }

    void CharacterCache::Level::Set(const int32_t& param)
    {
        m_owner.CharacterT::level = param;
        m_isBound = true;
    }

    auto CharacterCache::Level::Get() const
        -> const int32_t&
    {
        return m_owner.CharacterT::level;
    }

    std::string CharacterCache::Level::GetName() const
    {
        return "level";
    }

    std::string CharacterCache::Level::GetValueString() const
    {
        return std::to_string(m_owner.CharacterT::level);
    }

    bool CharacterCache::Level::IsBound() const
    {
        return m_isBound;
    };

    CharacterCache::Level& CharacterCache::GetLevel()
    {
        return *static_cast<CharacterCache::Level*>(m_pLevel);
    };

    auto CharacterCache::GetObjectName() const -> std::string
    {
        return "Character";
    };

    auto CharacterCache::GetFieldNames() const -> const std::vector<std::string>&
    {
        return m_names;
    };

    auto CharacterCache::GetFieldName(const int32_t fieldEnumValue) const -> std::string
    {
        NULL_RETURN(0 <= fieldEnumValue && fieldEnumValue < CHARACTER::MAX, std::string{});
        return m_names[fieldEnumValue];
    };

    auto CharacterCache::GetField(const std::string& fieldName) const -> const std::shared_ptr<CacheField>&
    {
        if (const auto found = m_fields.find(fieldName);
            found == m_fields.end())
            return nullptr;
         else
            return found->second;
    };

    auto CharacterCache::GetField(const int32_t fieldEnumValue) const -> const std::shared_ptr<CacheField>&
    {
        return GetField(GetFieldName(fieldEnumValue));
    };

}
