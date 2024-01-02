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
