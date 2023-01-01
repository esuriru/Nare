#pragma once

#ifdef NR_PLATFORM_WINDOWS
	#ifdef WIN32

	#else
		#error Nare only supports x86 (for now!)
	#endif

#else
	#error Nare only supports Windows (for now!)
#endif

#ifdef NR_ENABLE_ASSERTS
	#define NR_ASSERT(x, ...) { if (!(x)) { 
#endif

// Bit-shift to the left (multiply by 2)
#define BIT(x) (1 << (x))
