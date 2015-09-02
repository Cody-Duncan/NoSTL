
/*
Author: Cody Duncan
Date: August 4, 2015
Copyright: N/A
Witty Quote:
Description:
	A shim for getting some types implemented using stl for now.
	MUST BE REPLACED OVER TIME

*/

#pragma once

#ifndef Z_MACROS_H
#define Z_MACROS_H

// ---------- includes ---------


#define Zero_Struct(s) memset(&s, 0, sizeof(s));

#ifdef _MSC_VER
#define NO_OP __nop()
#else
#define NO_OP __asm nop
#endif

#endif