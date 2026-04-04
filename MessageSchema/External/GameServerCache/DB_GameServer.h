#pragma once

#include "D:\projects\zozo\MessageSchema\External\DB_GameServer_generated.h"

#include <Engine/Tx/CacheField.h>
#include <Engine/Tx/CacheObject.h>

namespace GenericBoson::Zozo
{
    enum CHARACTER
    {
        ID = 0,
        USER_ID = 1,
        NAME = 2,
        LEVEL = 3,
        MAX
    };

    class Id;
    class UserId;
    class Name;
    class Level;

    template<typename T>
    class CharacterCache : public T,
        private CharacterT,
        std::enable_shared_from_this<CharacterCache<T>>
    {
        friend class Id;
        friend class UserId;
        friend class Name;
        friend class Level;
    public:
       CharacterCache(CacheTx& tx);
        class Id : public CacheField
        {
        public:
            Id(CharacterCache& owner);
            void Set(const int64_t& param);
            bool Set(const std::string& value) override;
            void SetKey(const int64_t& param);
            auto Get() const -> const int64_t&;
            std::string GetName() const override;
            std::string GetValueString() const override;
            bool IsKey() const override;
            void Bind() override;
            bool IsBound() const override;
        private:
            CharacterCache& m_owner;
            FieldState m_state = FieldState::None;
        };
        Id& GetId();

        class UserId : public CacheField
        {
        public:
            UserId(CharacterCache& owner);
            void Set(const int64_t& param);
            bool Set(const std::string& value) override;
            void SetKey(const int64_t& param);
            auto Get() const -> const int64_t&;
            std::string GetName() const override;
            std::string GetValueString() const override;
            bool IsKey() const override;
            void Bind() override;
            bool IsBound() const override;
        private:
            CharacterCache& m_owner;
            FieldState m_state = FieldState::None;
        };
        UserId& GetUserId();

        class Name : public CacheField
        {
        public:
            Name(CharacterCache& owner);
            bool Set(const std::string& value) override;
            void SetKey(const std::string& param);
            auto Get() const -> const std::string&;
            std::string GetName() const override;
            std::string GetValueString() const override;
            bool IsKey() const override;
            void Bind() override;
            bool IsBound() const override;
        private:
            CharacterCache& m_owner;
            FieldState m_state = FieldState::None;
        };
        Name& GetName();

        class Level : public CacheField
        {
        public:
            Level(CharacterCache& owner);
            void Set(const int32_t& param);
            bool Set(const std::string& value) override;
            void SetKey(const int32_t& param);
            auto Get() const -> const int32_t&;
            std::string GetName() const override;
            std::string GetValueString() const override;
            bool IsKey() const override;
            void Bind() override;
            bool IsBound() const override;
        private:
            CharacterCache& m_owner;
            FieldState m_state = FieldState::None;
        };
        Level& GetLevel();

    protected:
        auto GetObjectName() const                            -> std::string                           override;
        auto GetFieldNames() const                            -> const std::vector<std::string>&       override;
        auto GetFieldName(const int32_t fieldEnumValue) const -> std::string                           override;
        auto GetField(const std::string& fieldName) const     -> const CacheField*                     override;
        auto GetField(const int32_t fieldEnumValue) const     -> const CacheField*                     override;
        auto GetFields() const                                -> const std::vector<const CacheField*>& override;
    private:
        CacheField* m_pId = nullptr;
        CacheField* m_pUserId = nullptr;
        CacheField* m_pName = nullptr;
        CacheField* m_pLevel = nullptr;

        std::vector<std::string> m_names = 
        {
            "id",
            "user_id",
            "name",
            "level"
        };

        std::unordered_map<std::string, std::shared_ptr<CacheField>> m_fieldMap;
        std::vector<const CacheField*>                               m_fieldVector;
    };

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
    bool CharacterCache<T>::Id::Set(const std::string& param)
    {
        m_owner.CharacterT::id = std::stol(param);
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
    bool CharacterCache<T>::UserId::Set(const std::string& param)
    {
        m_owner.CharacterT::user_id = std::stol(param);
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
    bool CharacterCache<T>::Name::Set(const std::string& param)
    {
        m_owner.CharacterT::name = (param);
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
    bool CharacterCache<T>::Level::Set(const std::string& param)
    {
        m_owner.CharacterT::level = std::stoi(param);
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
