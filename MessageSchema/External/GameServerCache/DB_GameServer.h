#pragma once

#include "D:\projects\zozo\MessageSchema\External\DB_GameServer_generated.h"

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

    class CharacterCache : private CharacterT
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

    private:
        int64_t m_id;
        int64_t m_user_id;
        std::string m_name;
        int32_t m_level;

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
