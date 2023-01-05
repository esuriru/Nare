#pragma once
#include "Log.h"

#ifdef NR_PLATFORM_WINDOWS
	#ifdef WIN32

	#else
		#error Nare only supports x86 (for now!)
	#endif

#else
	#error Nare only supports Windows (for now!)
#endif

#ifdef NR_ENABLE_ASSERTS
	#define NR_CORE_ASSERT(x, ...) { if (!(x)) { NR_CORE_ERROR("Nare Engine: Assertion Failed - ", __VA_ARGS__); __debugbreak(); } }
	#define NR_CLIENT_ASSERT(x, ...) { if (!(x)) { NR_CLIENT_ERROR("Nare Engine: Assertion Failed - ", __VA_ARGS__); __debugbreak(); } }
#else
	#define NR_CORE_ASSERT(x, ...)
	#define NR_CLIENT_ASSERT(x, ...)
#endif

// Bit-shift to the left (multiply by 2)
#define BIT(x) (1 << (x))

#define	NR_BIND_EVENT_FUNC(fn) std::bind(&(fn), this, std::placeholders::_1)