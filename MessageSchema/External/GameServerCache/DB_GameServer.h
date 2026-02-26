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

    class CharacterCache : 
        public CacheObject,
        private CharacterT,
        std::enable_shared_from_this<CharacterCache>
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
            auto Get() const -> const int64_t&;
            std::string GetName() const override;
            std::string GetValueString() const override;
            bool IsBound() const override;
        private:
            CharacterCache& m_owner;
            bool m_isBound = false;
        };
        Id& GetId();

        class UserId : public CacheField
        {
        public:
            UserId(CharacterCache& owner);
            void Set(const int64_t& param);
            auto Get() const -> const int64_t&;
            std::string GetName() const override;
            std::string GetValueString() const override;
            bool IsBound() const override;
        private:
            CharacterCache& m_owner;
            bool m_isBound = false;
        };
        UserId& GetUserId();

        class Name : public CacheField
        {
        public:
            Name(CharacterCache& owner);
            void Set(const std::string& param);
            auto Get() const -> const std::string&;
            std::string GetName() const override;
            std::string GetValueString() const override;
            bool IsBound() const override;
        private:
            CharacterCache& m_owner;
            bool m_isBound = false;
        };
        Name& GetName();

        class Level : public CacheField
        {
        public:
            Level(CharacterCache& owner);
            void Set(const int32_t& param);
            auto Get() const -> const int32_t&;
            std::string GetName() const override;
            std::string GetValueString() const override;
            bool IsBound() const override;
        private:
            CharacterCache& m_owner;
            bool m_isBound = false;
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
}
