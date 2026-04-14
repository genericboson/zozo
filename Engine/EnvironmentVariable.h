#pragma once

#include "Singleton.h"

#define ENV_DECL(type, name, defaultValue) \
private:\
	type m_##name = defaultValue;\
public:\
	static type Get##name() { return Environment::g_environmentVariable.m_##name; }\
	static void Set##name(const type& value) { Environment::g_environmentVariable.m_##name = value; }

namespace GenericBoson
{
	class Environment
	{
		ENV_DECL(int64_t, CharacterUpdatePeriodMs, 42);
		ENV_DECL(int64_t, DefaultUpdatePeriodMs, 42);

		ENV_DECL(std::string, DBHost,     "127.0.0.1");
		ENV_DECL(uint16_t,    DBPort,     3306);
		ENV_DECL(std::string, DBUser,     "root");
		ENV_DECL(std::string, DBPassword, "1234");
		ENV_DECL(std::string, DBName,     "zozo_game");

		ENV_DECL(int32_t, GetConnTimeoutMs, 10);
		ENV_DECL(int32_t, GetConnTrialCount, 3);

	private:
		static Environment g_environmentVariable;
	};
}