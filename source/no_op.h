/*
Author: Cody Duncan
Date: September 6, 2015
Copyright: N/A
Witty Quote:
Description:

*/

#pragma once

#ifndef Z_NO_OP_H
#define Z_NO_OP_H

#ifdef _MSC_VER
#define no_op __nop()
#else
#define NO_OP __asm nop
#endif

// TODO: no_op for other compilers

#endif

