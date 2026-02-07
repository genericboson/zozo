#pragma once

#include "D:\projects\zozo\MessageSchema\External\DB_GameServer_generated.h"

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
        private CharacterT
    {
    public:
        void SetId(const int64_t& param);
        const int64_t& GetId();

        void SetUser_id(const int64_t& param);
        const int64_t& GetUser_id();

        void SetName(const std::string& param);
        const std::string& GetName();

        void SetLevel(const int32_t& param);
        const int32_t& GetLevel();

    protected:
        auto GetObjectName() -> const std::string&              override;
        auto GetFieldNames() -> const std::vector<std::string>& override;
        bool IsFlagged(const int64_t field)  override;
    private:

        std::vector<std::string> m_names = 
        {
            "id",
            "user_id",
            "name",
            "level"
        };

        bool m_flags[4] = { false, };
    };
}
