#include "PCH.h"

#include "DB_GameServer.h"

#include <Engine/Concepts.h>

namespace GenericBoson::Zozo
{
    template<typename T>
    CharacterCache<T>::CharacterCache(CacheTx& tx)
        : T(tx)
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

    template<typename T>
    CharacterCache<T>::Id::Id(CharacterCache& owner)
        : m_owner(owner)
    {
    }

    template<typename T>
    void CharacterCache<T>::Id::Set(const int64_t& param)
    {
        m_owner.CharacterT::id = param;
        m_state = FieldState::Bound;
    }

    template<typename T>
    void CharacterCache<T>::Id::SetKey(const int64_t& param)
    {
        m_owner.CharacterT::id = param;
        m_state = FieldState::Key;
    }

    template<typename T>
    auto CharacterCache<T>::Id::Get() const
        -> const int64_t&
    {
        return m_owner.CharacterT::id;
    }

    template<typename T>
    std::string CharacterCache<T>::Id::GetName() const
    {
        return "id";
    }

    template<typename T>
    std::string CharacterCache<T>::Id::GetValueString() const
    {
        return std::to_string(m_owner.CharacterT::id);
    }

    template<typename T>
    void CharacterCache<T>::Id::Bind()
    {
        m_state = FieldState::Bound;
    };

    template<typename T>
    bool CharacterCache<T>::Id::IsBound() const
    {
        return m_state == FieldState::Bound || m_state == FieldState::Key;
    };

    template<typename T>
    bool CharacterCache<T>::Id::IsKey() const
    {
        return m_state == FieldState::Key;
    };

    template<typename T>
    CharacterCache<T>::Id& CharacterCache<T>::GetId()
    {
        return *static_cast<CharacterCache::Id*>(m_pId);
    };

    template<typename T>
    CharacterCache<T>::UserId::UserId(CharacterCache& owner)
        : m_owner(owner)
    {
    }

    template<typename T>
    void CharacterCache<T>::UserId::Set(const int64_t& param)
    {
        m_owner.CharacterT::user_id = param;
        m_state = FieldState::Bound;
    }

    template<typename T>
    void CharacterCache<T>::UserId::SetKey(const int64_t& param)
    {
        m_owner.CharacterT::user_id = param;
        m_state = FieldState::Key;
    }

    template<typename T>
    auto CharacterCache<T>::UserId::Get() const
        -> const int64_t&
    {
        return m_owner.CharacterT::user_id;
    }

    template<typename T>
    std::string CharacterCache<T>::UserId::GetName() const
    {
        return "user_id";
    }

    template<typename T>
    std::string CharacterCache<T>::UserId::GetValueString() const
    {
        return std::to_string(m_owner.CharacterT::user_id);
    }

    template<typename T>
    void CharacterCache<T>::UserId::Bind()
    {
        m_state = FieldState::Bound;
    };

    template<typename T>
    bool CharacterCache<T>::UserId::IsBound() const
    {
        return m_state == FieldState::Bound || m_state == FieldState::Key;
    };

    template<typename T>
    bool CharacterCache<T>::UserId::IsKey() const
    {
        return m_state == FieldState::Key;
    };

    template<typename T>
    CharacterCache<T>::UserId& CharacterCache<T>::GetUserId()
    {
        return *static_cast<CharacterCache::UserId*>(m_pUserId);
    };

    template<typename T>
    CharacterCache<T>::Name::Name(CharacterCache& owner)
        : m_owner(owner)
    {
    }

    template<typename T>
    void CharacterCache<T>::Name::Set(const std::string& param)
    {
        m_owner.CharacterT::name = param;
        m_state = FieldState::Bound;
    }

    template<typename T>
    void CharacterCache<T>::Name::SetKey(const std::string& param)
    {
        m_owner.CharacterT::name = param;
        m_state = FieldState::Key;
    }

    template<typename T>
    auto CharacterCache<T>::Name::Get() const
        -> const std::string&
    {
        return m_owner.CharacterT::name;
    }

    template<typename T>
    std::string CharacterCache<T>::Name::GetName() const
    {
        return "name";
    }

    template<typename T>
    std::string CharacterCache<T>::Name::GetValueString() const
    {
        return m_owner.CharacterT::name;
    }

    template<typename T>
    void CharacterCache<T>::Name::Bind()
    {
        m_state = FieldState::Bound;
    };

    template<typename T>
    bool CharacterCache<T>::Name::IsBound() const
    {
        return m_state == FieldState::Bound || m_state == FieldState::Key;
    };

    template<typename T>
    bool CharacterCache<T>::Name::IsKey() const
    {
        return m_state == FieldState::Key;
    };

    template<typename T>
    CharacterCache<T>::Name& CharacterCache<T>::GetName()
    {
        return *static_cast<CharacterCache::Name*>(m_pName);
    };

    template<typename T>
    CharacterCache<T>::Level::Level(CharacterCache& owner)
        : m_owner(owner)
    {
    }

    template<typename T>
    void CharacterCache<T>::Level::Set(const int32_t& param)
    {
        m_owner.CharacterT::level = param;
        m_state = FieldState::Bound;
    }

    template<typename T>
    void CharacterCache<T>::Level::SetKey(const int32_t& param)
    {
        m_owner.CharacterT::level = param;
        m_state = FieldState::Key;
    }

    template<typename T>
    auto CharacterCache<T>::Level::Get() const
        -> const int32_t&
    {
        return m_owner.CharacterT::level;
    }

    template<typename T>
    std::string CharacterCache<T>::Level::GetName() const
    {
        return "level";
    }

    template<typename T>
    std::string CharacterCache<T>::Level::GetValueString() const
    {
        return std::to_string(m_owner.CharacterT::level);
    }

    template<typename T>
    void CharacterCache<T>::Level::Bind()
    {
        m_state = FieldState::Bound;
    };

    template<typename T>
    bool CharacterCache<T>::Level::IsBound() const
    {
        return m_state == FieldState::Bound || m_state == FieldState::Key;
    };

    template<typename T>
    bool CharacterCache<T>::Level::IsKey() const
    {
        return m_state == FieldState::Key;
    };

    template<typename T>
    CharacterCache<T>::Level& CharacterCache<T>::GetLevel()
    {
        return *static_cast<CharacterCache::Level*>(m_pLevel);
    };

    template<typename T>
    auto CharacterCache<T>::GetObjectName() const -> std::string
    {
        return "Character";
    };

    template<typename T>
    auto CharacterCache<T>::GetFieldNames() const -> const std::vector<std::string>&
    {
        return m_names;
    };

    template<typename T>
    auto CharacterCache<T>::GetFieldName(const int32_t fieldEnumValue) const -> std::string
    {
        NULL_RETURN(0 <= fieldEnumValue && fieldEnumValue < CHARACTER::MAX, std::string{});
        return m_names[fieldEnumValue];
    };

    template<typename T>
    auto CharacterCache<T>::GetField(const std::string& fieldName) const -> const CacheField*
    {
        if (const auto found = m_fieldMap.find(fieldName);
            found == m_fieldMap.end())
            return nullptr;
         else
            return found->second.get();
    };

    template<typename T>
    auto CharacterCache<T>::GetField(const int32_t fieldEnumValue) const -> const CacheField*
    {
        return GetField(GetFieldName(fieldEnumValue));
    };

    template<typename T>
    auto CharacterCache<T>::GetFields() const -> const std::vector<const CacheField*>&
    {
        return m_fieldVector;
    };

}
