#pragma once

#include "Log.h"
#include <memory>

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

#define	NR_BIND_EVENT_FUNC(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Nare 
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	} 

	// TODO: To be handled by an asset manager
	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Scope<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	} 
}
