#pragma once

namespace GenericBoson
{
	struct Join_User_UserCharacter
	{
		int64_t     character_id;
		int64_t     user_id;
		std::string name;
		int32_t     level;
	};
}