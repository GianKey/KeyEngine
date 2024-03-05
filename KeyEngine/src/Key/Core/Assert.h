#pragma once

#ifdef KEY_DEBUG
	#define KEY_ENABLE_ASSERTS
#endif

#ifdef KEY_ENABLE_ASSERTS
	#define KEY_ASSERT_NO_MESSAGE(condition) { if(!(condition)) { KEY_ERROR("Assertion Failed"); __debugbreak(); } }
	#define KEY_ASSERT_MESSAGE(condition, ...) { if(!(condition)) { KEY_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

	#define KEY_ASSERT_RESOLVE(arg1, arg2, macro, ...) macro
	#define KEY_GET_ASSERT_MACRO(...) KEY_EXPAND_VARGS(KEY_ASSERT_RESOLVE(__VA_ARGS__, KEY_ASSERT_MESSAGE, KEY_ASSERT_NO_MESSAGE))

	#define KEY_ASSERT(...) KEY_EXPAND_VARGS( KEY_GET_ASSERT_MACRO(__VA_ARGS__)(__VA_ARGS__) )
	#define KEY_CORE_ASSERT(...) KEY_EXPAND_VARGS( KEY_GET_ASSERT_MACRO(__VA_ARGS__)(__VA_ARGS__) )
#else
	#define KEY_ASSERT(...)
	#define KEY_CORE_ASSERT(...)
#endif