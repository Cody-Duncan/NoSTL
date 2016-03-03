/*
Author: Cody Duncan
Date: August 4, 2015
Copyright: N/A
Witty Quote:
Description:

*/

#pragma once

#ifndef ASSERT_H
#define ASSERT_H

#ifdef _DEBUG

	// ---------- includes ---------
	#include "debug_print.h"


	// debug_break	
	#if defined(_WIN32)
		#define debug_break() __debugbreak()
	#else
		#define debug_break() static_assert(false, "No implementation of debug_break or assert for this platform")
	#endif


	//Halts the program if the condition is false. Prints the given message. Debug only.
	#define z_assert_message(condition, ...)			\
		do												\
		{												\
			if(!(condition)) 							\
			{ 											\
				debug_print(__VA_ARGS__);		\
				__debugbreak(); 						\
			}											\
		} while(0)

	//Halts the program if the condition is false. Debug only.
	#define z_assert(condition) \
		z_assert_message(condition, "")

	#define z_static_assert(condition, message) \
		static_assert(condition, message)

	#if  defined(__clang__)
		inline void donothing() {}
		#define breakpoint_nop() donothing()
	#elif defined( _WIN64 )
		#define breakpoint_nop() __nop()
	#elif _WIN32 
		#define breakpoint_nop() __asm nop
	#endif

#else
#define debug_break()
#define z_assert_message(condition, message, ...)
#define z_assert(condition)
#define z_static_assert(condition, message)
#define breakpoint_nop()

#endif
//END ifdef _DEBUG

#endif
//END ifdef _DEBUG
