#pragma once
#include "nostl\primitives.h"
#include <iostream>
#include <algorithm>
#include <limits>

#ifdef _MSC_VER
#pragma intrinsic(__rdtsc)
inline uint64 GetRDTSC()
{
	int a[4];
	__cpuid(a, 0x80000000);  // flush OOO instruction pipeline
	return __rdtsc();
}

extern uint64 g_correctionFactor;
extern uint64 g_accuracy;

inline void WarmupRDTSC()
{
	int a[4];
	__cpuid(a, 0x80000000);  // warmup cpuid.
	__cpuid(a, 0x80000000);
	__cpuid(a, 0x80000000);

	// measure the measurer overhead with the measurer (crazy he..)
	uint64 minDiff = 9223372036854775807LL; // LLONG_MAX;
	uint64 maxDiff = 0;   // this is going to help calculate our PRECISION ERROR MARGIN
	for(int i = 0; i < 80; ++i)
	{
		uint64 tick1 = GetRDTSC();
		uint64 tick2 = GetRDTSC();
		minDiff = std::min(minDiff, tick2 - tick1);   // make many takes, take the smallest that ever come.
		maxDiff = std::max(maxDiff, tick2 - tick1);
	}
	g_correctionFactor = minDiff;

	//printf("Correction factor %llu clocks\n", g_correctionFactor);

	g_accuracy = maxDiff - minDiff;
	//printf("Measurement Accuracy (in clocks) : %llu\n", g_accuracy);
}
#endif