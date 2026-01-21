#pragma once

namespace GenericBoson
{
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
        long m_id;
        long m_user_id;
        std::string m_name;
        int32_t m_level;
    }
}
