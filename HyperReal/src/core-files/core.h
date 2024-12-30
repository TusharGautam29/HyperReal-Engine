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

#define BIT(x) (1 << x)