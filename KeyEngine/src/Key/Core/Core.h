#pragma once
#include <memory>
#ifdef KEY_PLATFORM_WINDOWS
#if KEY_DYNAIMC_LINK
	#ifdef KEY_BUILD_DLL
		#define KEY_API __declspec(dllexport)
	#else
		#define KEY_API __declspec(dllimport)
	#endif KEY_BUILD_DLL
#else
	#define KEY_API
#endif 
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

namespace Key {
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}