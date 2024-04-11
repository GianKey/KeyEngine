#pragma once
#include <memory>
#include "Assert.h"
#include "Ref.h"
namespace Key {
	void InitializeCore();
	void ShutdownCore();
}

#ifndef KEY_PLATFORM_WINDOWS
	#error KeyEngine only supprt Windows!
#endif // KEY_PALTFORM_WINDOWS


#define KEY_EXPAND_VARGS(x) x

#define BIT(x) (1 << x)

/**
 * 使用 std::bind 来创建一个成员函数的绑定.
 * @param &x 函数地址
 * @param this 指向当前实例
 * @param std::placeholders::_1 一个占位符，表示在调用绑定的函数时，传递第一个参数
 */
#define KEY_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Key {
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	using byte = uint8_t;
}