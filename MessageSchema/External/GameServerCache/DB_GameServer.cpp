#include "PCH.h"

#include "DB_GameServer.h"

namespace GenericBoson::Zozo
{
    void CharacterCache::SetId(const int64_t& param)
    {
        m_id = param;
        m_flags[CHARACTER::ID] = true;
    }
    const int64_t& CharacterCache::GetId()
    {
        return m_id;
    }
    void CharacterCache::SetUser_id(const int64_t& param)
    {
        m_user_id = param;
        m_flags[CHARACTER::USER_ID] = true;
    }
    const int64_t& CharacterCache::GetUser_id()
    {
        return m_user_id;
    }
    void CharacterCache::SetName(const std::string& param)
    {
        m_name = param;
        m_flags[CHARACTER::NAME] = true;
    }
    const std::string& CharacterCache::GetName()
    {
        return m_name;
    }
    void CharacterCache::SetLevel(const int32_t& param)
    {
        m_level = param;
        m_flags[CHARACTER::LEVEL] = true;
    }
    const int32_t& CharacterCache::GetLevel()
    {
        return m_level;
    }
}
