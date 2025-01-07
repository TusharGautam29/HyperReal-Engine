#pragma once
#ifdef HR_PLATFORM_WINDOWS
	#ifdef HR_BUILD_DLL
		#define HyperR_API __declspec(dllexport)
	#else
		#define HyperR_API __declspec(dllimport)
	#endif
#else
	#error HyperReal only supports Windows!
#endif

#ifdef HR_ENABLE_ASSERTS
	#define HR_ASSERT(x, ...) { if(!(x)) { HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define HR_CORE_ASSERT(x, ...) { if(!(x)) { HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define HR_ASSERT(x, ...)
	#define HR_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)

#define HR_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)