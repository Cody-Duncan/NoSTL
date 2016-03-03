/*
Author: Cody Duncan
Date: August 4, 2015
Copyright: N/A
Witty Quote:
Description:

*/

#pragma once

#ifndef DEBUG_PRINT_H
#define DEBUG_PRINT_H

// ---------- includes ---------
#if defined(_WIN32)
#include <stdio.h>
#include <stdarg.h>
#endif

#if defined(_WIN32)

void OutputDebugString_fwd(const char*);

inline void internal_debug_print(const char* szFormat, ...)
{
	char szBuff[1024];
	szBuff[1023] = 0; // null terminate
	va_list arg;
	va_start(arg, szFormat);
	_vsnprintf_s(szBuff, sizeof(szBuff), szFormat, arg);
	va_end(arg);

	OutputDebugString_fwd(szBuff);
}

#define debug_print(...) internal_debug_print(__VA_ARGS__)

#else
#define debug_print(message, ...) static_assert(false, "No implementation of debug_print or assert(condition, message) for this platform")
#endif
//END if defined(_WIN32)

#endif
//END ifndef Z_DEBUG_PRINT_H