/*
Author: Cody Duncan
Date: August 4, 2015
Copyright: N/A
Witty Quote:
Description:

*/

#pragma once

#ifndef PRIMITIVES_H
#define PRIMITIVES_H

// ---------- includes ---------

namespace nostl
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
using uint = nostl::uint;

//unsigned char
using uchar = nostl::uchar;

//char
using int8 =  nostl::int8;

//short
using int16 = nostl::int16;

//int
using int32 = nostl::int32;

//__int64
using int64 = nostl::int64;

//unsigned char
using uint8 =  nostl::uint8;

//unsigned short
using uint16 = nostl::uint16;

//unsigned int
using uint32 = nostl::uint32;

//unsigned __int64
using uint64 = nostl::uint64;

#endif

#endif