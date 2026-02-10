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

    class CharacterCache : 
        public CacheObject,
        private CharacterT,
        std::enable_shared_from_this<CharacterCache>
    {
        friend class Id;
        friend class User_id;
        friend class Name;
        friend class Level;
    public:
       CharacterCache();
        class Id : public CacheField
        {
        public:
            Id(CharacterCache& owner);
            void Set(const int64_t& param);
            auto Get() const -> const int64_t&;
            std::string GetName() const;
            bool IsFlagged() const override;
        private:
            CharacterCache& m_owner;
            bool m_flag = false;
        };

        class User_id : public CacheField
        {
        public:
            User_id(CharacterCache& owner);
            void Set(const int64_t& param);
            auto Get() const -> const int64_t&;
            std::string GetName() const;
            bool IsFlagged() const override;
        private:
            CharacterCache& m_owner;
            bool m_flag = false;
        };

        class Name : public CacheField
        {
        public:
            Name(CharacterCache& owner);
            void Set(const std::string& param);
            auto Get() const -> const std::string&;
            std::string GetName() const;
            bool IsFlagged() const override;
        private:
            CharacterCache& m_owner;
            bool m_flag = false;
        };

        class Level : public CacheField
        {
        public:
            Level(CharacterCache& owner);
            void Set(const int32_t& param);
            auto Get() const -> const int32_t&;
            std::string GetName() const;
            bool IsFlagged() const override;
        private:
            CharacterCache& m_owner;
            bool m_flag = false;
        };

    protected:
        auto GetObjectName() -> std::string                     override;
        auto GetFieldNames() -> const std::vector<std::string>& override;
    private:

        std::vector<std::string> m_names = 
        {
            "id",
            "user_id",
            "name",
            "level"
        };

        std::unordered_map<int64_t, std::shared_ptr<CacheField>> m_fields;
    };
}
