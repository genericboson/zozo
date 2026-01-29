#pragma once

#include "D:\projects\zozo\MessageSchema\External\DB_GameServer_generated.h"

namespace GenericBoson::Zozo
{
    enum class CHARACTER
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
        void SetId();
        void GetId();
        void SetUser_id();
        void GetUser_id();
        void SetName();
        void GetName();
        void SetLevel();
        void GetLevel();

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
