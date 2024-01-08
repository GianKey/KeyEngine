#pragma once

#ifdef KEY_PLATFORM_WINDOWS
	#ifdef KEY_BUILD_DLL
		#define KEY_API __declspec(dllexport)
	#else
		#define KEY_API __declspec(dllimport)
	#endif KEY_BUILD_DLL
#else
	#error KeyEngine only supprt Windows!
#endif // KEY_PALTFORM_WINDOWS

#ifdef KEY_ENABLE_ASSERTS
	#define KEY_ASSERT(x, ...) {if(!x) {KEY_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define KEY_CORE_ASSERT(x, ...) {if(!x) {KEY_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define KEY_ASSERT(x, ...)
	#define KEY_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)

#define KEY_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)