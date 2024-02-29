#pragma once

#ifdef WINDOW_PLATFORM_DLL
	#ifdef HZ_DYNAMIC_LINK
		#ifdef GE_BUILD_DLL
			#define GE_API _declspec(dllexport)
		#else
			#define GE_API _declspec(dllimport)
		#endif
	#else
		#define GE_API
	#endif
#endif

#ifdef ENABLE_ASSERT
	#define GE_CORE_ASSERT(x, ...)  { if(!x) { GE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define GE_ASSERT(x, ...)       { if(!x) { GE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
	#define GE_CORE_ASSERT(x, ...)
	#define GE_ASSERT(x, ...)
#endif

#define Bit(x)  1 << x