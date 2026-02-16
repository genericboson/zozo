#pragma once

namespace GenericBoson
{
	struct CharacterList_Select_UserCharacter
	{
		int64_t                    id;
		int64_t                    user_id;
		std::optional<std::string> name;
		std::optional<int32_t>     level;
	};
}