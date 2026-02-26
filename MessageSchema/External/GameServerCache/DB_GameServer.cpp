#include "PCH.h"

#include "DB_GameServer.h"

#include <Engine/Concepts.h>

namespace GenericBoson::Zozo
{
    CharacterCache::CharacterCache(CacheTx& tx)
        : CacheObject(tx)
    {
        m_fieldVector.reserve(4);
        m_fieldMap["id"] = std::make_shared<Id>(*this);
        m_pId = m_fieldMap["id"].get();
        m_fieldVector.push_back(m_pId);
        m_fieldMap["user_id"] = std::make_shared<UserId>(*this);
        m_pUserId = m_fieldMap["user_id"].get();
        m_fieldVector.push_back(m_pUserId);
        m_fieldMap["name"] = std::make_shared<Name>(*this);
        m_pName = m_fieldMap["name"].get();
        m_fieldVector.push_back(m_pName);
        m_fieldMap["level"] = std::make_shared<Level>(*this);
        m_pLevel = m_fieldMap["level"].get();
        m_fieldVector.push_back(m_pLevel);
    };

    CharacterCache::Id::Id(CharacterCache& owner)
        : m_owner(owner)
    {
    }

    void CharacterCache::Id::Set(const int64_t& param)
    {
        m_owner.CharacterT::id = param;
        m_state = FieldState::Bound;
    }

    void CharacterCache::Id::SetKey(const int64_t& param)
    {
        m_owner.CharacterT::id = param;
        m_state = FieldState::Key;
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

    void CharacterCache::Id::Bind()
    {
        m_state = FieldState::Bound;
    };

    bool CharacterCache::Id::IsBound() const
    {
        return m_state == FieldState::Bound || m_state == FieldState::Key;
    };

    bool CharacterCache::Id::IsKey() const
    {
        return m_state == FieldState::Key;
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
        m_state = FieldState::Bound;
    }

    void CharacterCache::UserId::SetKey(const int64_t& param)
    {
        m_owner.CharacterT::user_id = param;
        m_state = FieldState::Key;
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

    void CharacterCache::UserId::Bind()
    {
        m_state = FieldState::Bound;
    };

    bool CharacterCache::UserId::IsBound() const
    {
        return m_state == FieldState::Bound || m_state == FieldState::Key;
    };

    bool CharacterCache::UserId::IsKey() const
    {
        return m_state == FieldState::Key;
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
        m_state = FieldState::Bound;
    }

    void CharacterCache::Name::SetKey(const std::string& param)
    {
        m_owner.CharacterT::name = param;
        m_state = FieldState::Key;
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

    void CharacterCache::Name::Bind()
    {
        m_state = FieldState::Bound;
    };

    bool CharacterCache::Name::IsBound() const
    {
        return m_state == FieldState::Bound || m_state == FieldState::Key;
    };

    bool CharacterCache::Name::IsKey() const
    {
        return m_state == FieldState::Key;
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
        m_state = FieldState::Bound;
    }

    void CharacterCache::Level::SetKey(const int32_t& param)
    {
        m_owner.CharacterT::level = param;
        m_state = FieldState::Key;
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

    void CharacterCache::Level::Bind()
    {
        m_state = FieldState::Bound;
    };

    bool CharacterCache::Level::IsBound() const
    {
        return m_state == FieldState::Bound || m_state == FieldState::Key;
    };

    bool CharacterCache::Level::IsKey() const
    {
        return m_state == FieldState::Key;
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

    auto CharacterCache::GetField(const std::string& fieldName) const -> const CacheField*
    {
        if (const auto found = m_fieldMap.find(fieldName);
            found == m_fieldMap.end())
            return nullptr;
         else
            return found->second.get();
    };

    auto CharacterCache::GetField(const int32_t fieldEnumValue) const -> const CacheField*
    {
        return GetField(GetFieldName(fieldEnumValue));
    };

    auto CharacterCache::GetFields() const -> const std::vector<const CacheField*>&
    {
        return m_fieldVector;
    };

}
