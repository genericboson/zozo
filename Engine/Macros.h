#pragma once

namespace GenericBoson
{
#define WARNING_LOG( formatString, ... )         \
    printf( formatString, __VA_ARGS__ );

#define NULL_RETURN( expression, returnValue )   \
	if (!(expression))                           \
	{                                            \
		WARNING_LOG("Null = '" #expression "'"); \
		return returnValue;                      \
	}
}