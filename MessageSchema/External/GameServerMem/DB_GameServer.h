#pragma once

#include "D:\projects\zozo\MessageSchema\External\DB_GameServer_generated.h"

#include <Engine/Tx/MemField.h>
#include <Engine/Tx/MemObject.h>

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
    class CharacterMem : public T,
        private CharacterT,
        std::enable_shared_from_this<CharacterMem<T>>
    {
        friend class Id;
        friend class UserId;
        friend class Name;
        friend class Level;
    public:
        CharacterMem(MemTx& tx);
        std::shared_ptr<IMemObject> CreateObject() override;

        class Id : public MemField
        {
        public:
            Id(CharacterMem& owner);
            void Set(const int64_t& param);
            void Set(const boost::mysql::field_view value) override;
            void SetKey(const int64_t& param);
            auto Get() const -> const int64_t&;
            std::string GetName() const override;
            std::string GetValueString() const override;
            bool IsKey() const override;
            void Bind() override;
            bool IsBound() const override;
        private:
            CharacterMem& m_owner;
            FieldState m_state = FieldState::None;
        };
        Id& GetId();

        class UserId : public MemField
        {
        public:
            UserId(CharacterMem& owner);
            void Set(const int64_t& param);
            void Set(const boost::mysql::field_view value) override;
            void SetKey(const int64_t& param);
            auto Get() const -> const int64_t&;
            std::string GetName() const override;
            std::string GetValueString() const override;
            bool IsKey() const override;
            void Bind() override;
            bool IsBound() const override;
        private:
            CharacterMem& m_owner;
            FieldState m_state = FieldState::None;
        };
        UserId& GetUserId();

        class Name : public MemField
        {
        public:
            Name(CharacterMem& owner);
            void Set(const boost::mysql::field_view value) override;
            void SetKey(const std::string& param);
            auto Get() const -> const std::string&;
            std::string GetName() const override;
            std::string GetValueString() const override;
            bool IsKey() const override;
            void Bind() override;
            bool IsBound() const override;
        private:
            CharacterMem& m_owner;
            FieldState m_state = FieldState::None;
        };
        Name& GetName();

        class Level : public MemField
        {
        public:
            Level(CharacterMem& owner);
            void Set(const int32_t& param);
            void Set(const boost::mysql::field_view value) override;
            void SetKey(const int32_t& param);
            auto Get() const -> const int32_t&;
            std::string GetName() const override;
            std::string GetValueString() const override;
            bool IsKey() const override;
            void Bind() override;
            bool IsBound() const override;
        private:
            CharacterMem& m_owner;
            FieldState m_state = FieldState::None;
        };
        Level& GetLevel();

    protected:
        auto GetObjectName() const                            -> std::string                           override;
        auto GetFieldNames() const                            -> const std::vector<std::string>&       override;
        auto GetFieldName(const int32_t fieldEnumValue) const -> std::string                           override;
        auto GetField(const std::string& fieldName) const     -> const MemField*                     override;
        auto GetField(const int32_t fieldEnumValue) const     -> const MemField*                     override;
        auto GetFields() const                                -> const std::vector<const MemField*>& override;
    private:
        MemField* m_pId = nullptr;
        MemField* m_pUserId = nullptr;
        MemField* m_pName = nullptr;
        MemField* m_pLevel = nullptr;

        std::vector<std::string> m_names = 
        {
            "id",
            "user_id",
            "name",
            "level"
        };

        std::unordered_map<std::string, std::shared_ptr<MemField>> m_fieldMap;
        std::vector<const MemField*>                               m_fieldVector;
    };

    template<typename T>
    CharacterMem<T>::CharacterMem(MemTx& tx)
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
    std::shared_ptr<IMemObject> CharacterMem<T>::CreateObject()
    {
        return std::make_shared<CharacterMem<T>>(this->m_tx);
    };

    template<typename T>
    CharacterMem<T>::Id::Id(CharacterMem& owner)
        : m_owner(owner)
    {
    }

    template<typename T>
    void CharacterMem<T>::Id::Set(const int64_t& param)
    {
        m_owner.CharacterT::id = param;
        m_state = FieldState::Bound;
    }

    template<typename T>
    void CharacterMem<T>::Id::Set(const boost::mysql::field_view param)
    {
        m_owner.CharacterT::id = param.as_int64();
        m_state = FieldState::Bound;
    }

    template<typename T>
    void CharacterMem<T>::Id::SetKey(const int64_t& param)
    {
        m_owner.CharacterT::id = param;
        m_state = FieldState::Key;
    }

    template<typename T>
    auto CharacterMem<T>::Id::Get() const
        -> const int64_t&
    {
        return m_owner.CharacterT::id;
    }

    template<typename T>
    std::string CharacterMem<T>::Id::GetName() const
    {
        return "id";
    }

    template<typename T>
    std::string CharacterMem<T>::Id::GetValueString() const
    {
        return std::to_string(m_owner.CharacterT::id);
    }

    template<typename T>
    void CharacterMem<T>::Id::Bind()
    {
        m_state = FieldState::Bound;
    };

    template<typename T>
    bool CharacterMem<T>::Id::IsBound() const
    {
        return m_state == FieldState::Bound || m_state == FieldState::Key;
    };

    template<typename T>
    bool CharacterMem<T>::Id::IsKey() const
    {
        return m_state == FieldState::Key;
    };

    template<typename T>
    CharacterMem<T>::Id& CharacterMem<T>::GetId()
    {
        return *static_cast<CharacterMem::Id*>(m_pId);
    };

    template<typename T>
    CharacterMem<T>::UserId::UserId(CharacterMem& owner)
        : m_owner(owner)
    {
    }

    template<typename T>
    void CharacterMem<T>::UserId::Set(const int64_t& param)
    {
        m_owner.CharacterT::user_id = param;
        m_state = FieldState::Bound;
    }

    template<typename T>
    void CharacterMem<T>::UserId::Set(const boost::mysql::field_view param)
    {
        m_owner.CharacterT::user_id = param.as_int64();
        m_state = FieldState::Bound;
    }

    template<typename T>
    void CharacterMem<T>::UserId::SetKey(const int64_t& param)
    {
        m_owner.CharacterT::user_id = param;
        m_state = FieldState::Key;
    }

    template<typename T>
    auto CharacterMem<T>::UserId::Get() const
        -> const int64_t&
    {
        return m_owner.CharacterT::user_id;
    }

    template<typename T>
    std::string CharacterMem<T>::UserId::GetName() const
    {
        return "user_id";
    }

    template<typename T>
    std::string CharacterMem<T>::UserId::GetValueString() const
    {
        return std::to_string(m_owner.CharacterT::user_id);
    }

    template<typename T>
    void CharacterMem<T>::UserId::Bind()
    {
        m_state = FieldState::Bound;
    };

    template<typename T>
    bool CharacterMem<T>::UserId::IsBound() const
    {
        return m_state == FieldState::Bound || m_state == FieldState::Key;
    };

    template<typename T>
    bool CharacterMem<T>::UserId::IsKey() const
    {
        return m_state == FieldState::Key;
    };

    template<typename T>
    CharacterMem<T>::UserId& CharacterMem<T>::GetUserId()
    {
        return *static_cast<CharacterMem::UserId*>(m_pUserId);
    };

    template<typename T>
    CharacterMem<T>::Name::Name(CharacterMem& owner)
        : m_owner(owner)
    {
    }

    template<typename T>
    void CharacterMem<T>::Name::Set(const boost::mysql::field_view param)
    {
        m_owner.CharacterT::name = param.as_string();
        m_state = FieldState::Bound;
    }

    template<typename T>
    void CharacterMem<T>::Name::SetKey(const std::string& param)
    {
        m_owner.CharacterT::name = param;
        m_state = FieldState::Key;
    }

    template<typename T>
    auto CharacterMem<T>::Name::Get() const
        -> const std::string&
    {
        return m_owner.CharacterT::name;
    }

    template<typename T>
    std::string CharacterMem<T>::Name::GetName() const
    {
        return "name";
    }

    template<typename T>
    std::string CharacterMem<T>::Name::GetValueString() const
    {
        return m_owner.CharacterT::name;
    }

    template<typename T>
    void CharacterMem<T>::Name::Bind()
    {
        m_state = FieldState::Bound;
    };

    template<typename T>
    bool CharacterMem<T>::Name::IsBound() const
    {
        return m_state == FieldState::Bound || m_state == FieldState::Key;
    };

    template<typename T>
    bool CharacterMem<T>::Name::IsKey() const
    {
        return m_state == FieldState::Key;
    };

    template<typename T>
    CharacterMem<T>::Name& CharacterMem<T>::GetName()
    {
        return *static_cast<CharacterMem::Name*>(m_pName);
    };

    template<typename T>
    CharacterMem<T>::Level::Level(CharacterMem& owner)
        : m_owner(owner)
    {
    }

    template<typename T>
    void CharacterMem<T>::Level::Set(const int32_t& param)
    {
        m_owner.CharacterT::level = param;
        m_state = FieldState::Bound;
    }

    template<typename T>
    void CharacterMem<T>::Level::Set(const boost::mysql::field_view param)
    {
        m_owner.CharacterT::level = static_cast<int32_t>(param.as_int64());
        m_state = FieldState::Bound;
    }

    template<typename T>
    void CharacterMem<T>::Level::SetKey(const int32_t& param)
    {
        m_owner.CharacterT::level = param;
        m_state = FieldState::Key;
    }

    template<typename T>
    auto CharacterMem<T>::Level::Get() const
        -> const int32_t&
    {
        return m_owner.CharacterT::level;
    }

    template<typename T>
    std::string CharacterMem<T>::Level::GetName() const
    {
        return "level";
    }

    template<typename T>
    std::string CharacterMem<T>::Level::GetValueString() const
    {
        return std::to_string(m_owner.CharacterT::level);
    }

    template<typename T>
    void CharacterMem<T>::Level::Bind()
    {
        m_state = FieldState::Bound;
    };

    template<typename T>
    bool CharacterMem<T>::Level::IsBound() const
    {
        return m_state == FieldState::Bound || m_state == FieldState::Key;
    };

    template<typename T>
    bool CharacterMem<T>::Level::IsKey() const
    {
        return m_state == FieldState::Key;
    };

    template<typename T>
    CharacterMem<T>::Level& CharacterMem<T>::GetLevel()
    {
        return *static_cast<CharacterMem::Level*>(m_pLevel);
    };

    template<typename T>
    auto CharacterMem<T>::GetObjectName() const -> std::string
    {
        return "Character";
    };

    template<typename T>
    auto CharacterMem<T>::GetFieldNames() const -> const std::vector<std::string>&
    {
        return m_names;
    };

    template<typename T>
    auto CharacterMem<T>::GetFieldName(const int32_t fieldEnumValue) const -> std::string
    {
        NULL_RETURN(0 <= fieldEnumValue && fieldEnumValue < CHARACTER::MAX, std::string{});
        return m_names[fieldEnumValue];
    };

    template<typename T>
    auto CharacterMem<T>::GetField(const std::string& fieldName) const -> const MemField*
    {
        if (const auto found = m_fieldMap.find(fieldName);
            found == m_fieldMap.end())
            return nullptr;
         else
            return found->second.get();
    };

    template<typename T>
    auto CharacterMem<T>::GetField(const int32_t fieldEnumValue) const -> const MemField*
    {
        return GetField(GetFieldName(fieldEnumValue));
    };

    template<typename T>
    auto CharacterMem<T>::GetFields() const -> const std::vector<const MemField*>&
    {
        return m_fieldVector;
    };

}
