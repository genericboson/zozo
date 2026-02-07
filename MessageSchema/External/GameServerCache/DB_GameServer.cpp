#include "PCH.h"

#include "DB_GameServer.h"

namespace GenericBoson::Zozo
{
    void CharacterCache::SetId(const int64_t& param)
    {
        CharacterT::id = param;
        m_flags[CHARACTER::ID] = true;
    }

    const int64_t& CharacterCache::GetId()
    {
        return CharacterT::id;
    }

    auto CharacterCache::GetFieldNames() -> const std::vector<std::string>&
    {
        return m_names;
    };

    auto CharacterCache::GetObjectName() -> const std::vector<std::string>&
    {
        return Character;
    };

    bool CharacterCache::IsFlagged(const int64_t field)
    {
        return m_flags[field];
    };

    void CharacterCache::SetUser_id(const int64_t& param)
    {
        CharacterT::user_id = param;
        m_flags[CHARACTER::USER_ID] = true;
    }

    const int64_t& CharacterCache::GetUser_id()
    {
        return CharacterT::user_id;
    }

    auto CharacterCache::GetFieldNames() -> const std::vector<std::string>&
    {
        return m_names;
    };

    auto CharacterCache::GetObjectName() -> const std::vector<std::string>&
    {
        return Character;
    };

    bool CharacterCache::IsFlagged(const int64_t field)
    {
        return m_flags[field];
    };

    void CharacterCache::SetName(const std::string& param)
    {
        CharacterT::name = param;
        m_flags[CHARACTER::NAME] = true;
    }

    const std::string& CharacterCache::GetName()
    {
        return CharacterT::name;
    }

    auto CharacterCache::GetFieldNames() -> const std::vector<std::string>&
    {
        return m_names;
    };

    auto CharacterCache::GetObjectName() -> const std::vector<std::string>&
    {
        return Character;
    };

    bool CharacterCache::IsFlagged(const int64_t field)
    {
        return m_flags[field];
    };

    void CharacterCache::SetLevel(const int32_t& param)
    {
        CharacterT::level = param;
        m_flags[CHARACTER::LEVEL] = true;
    }

    const int32_t& CharacterCache::GetLevel()
    {
        return CharacterT::level;
    }

    auto CharacterCache::GetFieldNames() -> const std::vector<std::string>&
    {
        return m_names;
    };

    auto CharacterCache::GetObjectName() -> const std::vector<std::string>&
    {
        return Character;
    };

    bool CharacterCache::IsFlagged(const int64_t field)
    {
        return m_flags[field];
    };

}
