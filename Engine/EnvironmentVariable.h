#pragma once

#include "Singleton.h"

#define ENV_DECL(type, name, defaultValue) \
private:\
	type m_##name = defaultValue;\
public:\
	static type Get##name() { return Environment::g_environmentVariable.m_##name; }\
	static void Set##name(int value) { Environment::g_environmentVariable.m_##name = value; }

namespace GenericBoson
{
	class Environment
	{
		ENV_DECL(int64_t, CharacterUpdatePeriodMs, 42);
	private:
		static Environment g_environmentVariable;
	};
}