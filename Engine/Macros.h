#pragma once

namespace GenericBoson
{
#define ERROR_LOG( formatString, ... )         \
    std::cout <<"\033[1;31m"<<std::format( formatString, __VA_ARGS__ )<<"\033[0m"<<'\n';

#define WARN_LOG( formatString, ... )         \
    std::cout <<"\033[1;33m"<<std::format( formatString, __VA_ARGS__ )<<"\033[0m"<<'\n';

#define INFO_LOG( formatString, ... )         \
    std::cout <<"\033[1;32m"<<std::format( formatString, __VA_ARGS__ )<<"\033[0m"<<'\n';

#define NULL_RETURN( expression )   \
	if (!(expression))                           \
	{                                            \
		WARN_LOG("Null = '" #expression "'"); \
		return;                      \
	}

#define NULL_CONTINUE( expression )   \
	if (!(expression))                           \
	{                                            \
		WARN_LOG("Null = '" #expression "'"); \
		continue;                      \
	}

#define NULL_RETURN( expression, returnValue )   \
	if (!(expression))                           \
	{                                            \
		WARN_LOG("Null = '" #expression "'"); \
		return returnValue;                      \
	}

#define NULL_CO_VOID_RETURN( expression )   \
	if (!(expression))                           \
	{                                            \
		WARN_LOG("Null = '" #expression "'"); \
		co_return;                      \
	}

#define NULL_CO_RETURN( expression, returnValue )   \
	if (!(expression))                           \
	{                                            \
		WARN_LOG("Null = '" #expression "'"); \
		co_return returnValue;                      \
	}

#define CO_SLEEP_MS(time_value) \
	asio::steady_timer(co_await asio::this_coro::executor, std::chrono::milliseconds(time_value)).async_wait(asio::use_awaitable)
}