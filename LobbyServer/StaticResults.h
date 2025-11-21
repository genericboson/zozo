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
		int64_t                    id;
		std::optional<std::string> password;
	};

	struct RegisterReq_Select_GameServer
	{
		std::string db_ip;
		std::string db_account;
		std::string db_password;
		std::string db_main_schema;
		std::string server_name;
		int32_t     db_port;
		int32_t     listen_port;
		int32_t     max_ccu;
	};
}