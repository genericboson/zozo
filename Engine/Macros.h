#pragma once

namespace GenericBoson
{
#define WARN_LOG( formatString, ... )         \
    printf( formatString, __VA_ARGS__ );

#define INFO_LOG( formatString, ... )         \
    printf( formatString, __VA_ARGS__ );

#define NULL_RETURN( expression, returnValue )   \
	if (!(expression))                           \
	{                                            \
		WARN_LOG("Null = '" #expression "'"); \
		return returnValue;                      \
	}
}