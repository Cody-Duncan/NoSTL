#include "debug_print.h"

#include <cstdarg>
#include <stdio.h>
#include <wtypes.h>
#include <Windows.h>

void OutputDebugString_fwd(const char* szBuff)
{
	OutputDebugString(szBuff);
}