#pragma once

namespace GenericBoson
{
	struct Join_User_UserCharacter
	{
		std::optional<int64_t>     character_id;
		std::optional<int64_t>     user_id;
		std::optional<std::string> name;
		std::optional<int32_t>     level;
	};

	struct AuthReq_Select_User
	{
		std::optional<std::string> password;
	};
}