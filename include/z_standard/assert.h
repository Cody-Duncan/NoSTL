/*
Author: Cody Duncan
Date: August 4, 2015
Copyright: N/A
Witty Quote:
Description:

*/

#pragma once

#ifndef Z_ASSERT_H
#define Z_ASSERT_H

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
	#define assert_message(condition, message, ...)				\
		do												\
		{												\
			if(!(condition)) 							\
			{ 											\
				debug_print(message, __VA_ARGS__);		\
				__debugbreak(); 						\
			}											\
		} while(0)

	//Halts the program if the condition is false. Debug only.
	#define assert(condition) \
		assert_message(condition, "")

#else
#define debug_break()
#define assert_message(condition, message, ...)
#define assert(condition)

#endif
//END ifdef _DEBUG

#endif
//END ifdef _DEBUG
