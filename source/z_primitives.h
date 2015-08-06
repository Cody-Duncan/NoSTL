/*
Author: Cody Duncan
Date: August 4, 2015
Copyright: N/A
Witty Quote:
Description:

*/

#pragma once

#ifndef Z_PRIMITIVES_H
#define Z_PRIMITIVES_H

// ---------- includes ---------

namespace z
{
	typedef unsigned int uint;
	typedef unsigned char uchar;

	typedef char int8;
	typedef short int16;
	typedef int int32;
	typedef __int64 int64;

	typedef unsigned char uint8;
	typedef unsigned short uint16;
	typedef unsigned int uint32;
	typedef unsigned __int64 uint64;
}

#ifndef DONT_USE_Z_PRIMITIVE_GLOBAL_ALIAS

//unsigned int
using uint = z::uint;

//unsigned char
using uchar = z::uchar;

//char
using int8 =  z::int8;

//short
using int16 = z::int16;

//int
using int32 = z::int32;

//__int64
using int64 = z::int64;

//unsigned char
using uint8 =  z::uint8;

//unsigned short
using uint16 = z::uint16;

//unsigned int
using uint32 = z::uint32;

//unsigned __int64
using uint64 = z::uint64;

#endif

#endif