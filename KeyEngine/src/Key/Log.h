#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"

namespace Key {
	class KEY_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//core log macros
#define KEY_CORE_TRACE(...) ::Key::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define KEY_CORE_INFO(...) ::Key::Log::GetCoreLogger()->info(__VA_ARGS__)
#define KEY_CORE_WARN(...) ::Key::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define KEY_CORE_ERROR(...) ::Key::Log::GetCoreLogger()->error(__VA_ARGS__)
#define KEY_CORE_FATAL(...) ::Key::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client log macros
#define KEY_TRACE(...)  ::Key::Log::GetClientLogger()->trace(__VA_ARGS__)
#define KEY_INFO(...)	::Key::Log::GetClientLogger()->info(__VA_ARGS__)
#define KEY_WARN(...)	::Key::Log::GetClientLogger()->warn(__VA_ARGS__)
#define KEY_ERROR(...)  ::Key::Log::GetClientLogger()->error(__VA_ARGS__)
#define KEY_FATAL(...)  ::Key::Log::GetClientLogger()->fatal(__VA_ARGS__)


