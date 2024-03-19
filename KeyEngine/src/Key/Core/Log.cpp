#include "Kpch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/sinks/file_sinks.h"

#include <filesystem>

namespace Key {
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init() {
		// Create "logs" directory if doesn't exist
		std::string logsDirectory = "logs";
		if (!std::filesystem::exists(logsDirectory))
			std::filesystem::create_directories(logsDirectory);

		spdlog::set_pattern("%^[%T]%n: %v%$");


		std::vector<spdlog::sink_ptr> KeySinks =
		{
			std::make_shared<spdlog::sinks::stdout_sink_mt>(),
			std::make_shared<spdlog::sinks::simple_file_sink_mt>("logs/Key.log", true)
		};

		std::vector<spdlog::sink_ptr> appSinks =
		{
			std::make_shared<spdlog::sinks::stdout_sink_mt>(),
			std::make_shared<spdlog::sinks::simple_file_sink_mt>("logs/APP.log", true)
		};

		s_CoreLogger = std::make_shared<spdlog::logger>("Key", KeySinks.begin(), KeySinks.end());
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = std::make_shared<spdlog::logger>("APP", appSinks.begin(), appSinks.end());
		s_ClientLogger->set_level(spdlog::level::trace);
	}

	void Log::Shutdown()
	{
		s_ClientLogger.reset();
		s_CoreLogger.reset();
		spdlog::drop_all();
	}

}
