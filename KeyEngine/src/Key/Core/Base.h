#pragma once
#include <memory>
#include "Assert.h"
namespace Key {
	void InitializeCore();
	void ShutdownCore();
}

#ifndef KEY_PLATFORM_WINDOWS
	#error KeyEngine only supprt Windows!
#endif // KEY_PALTFORM_WINDOWS


#define KEY_EXPAND_VARGS(x) x

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
	using byte = unsigned char;
}