#include "Kpch.h"
#include "Window.h"

#ifdef KEY_PLATFORM_WINDOWS
#include "Key/Platform/Windows/WindowsWindow.h"
#endif

//namespace Key
//{
//	std::unique_ptr<Window> Window::Create(const WindowProps& props)
//	{
//#ifdef KEY_PLATFORM_WINDOWS
//		return std::make_unique<WindowsWindow>(props);
//#else
//		KEY_CORE_ASSERT(false, "Unknown platform!");
//		return nullptr;
//#endif
//	}
//
//}