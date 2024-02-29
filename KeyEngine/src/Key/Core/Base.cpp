#include "Kpch.h"
#include "Base.h"

#include "Log.h"

#define KEY_BUILD_ID "v0.1a"

namespace Key {

	void InitializeCore()
	{
		Key::Log::Init();

		KEY_CORE_TRACE("Key Engine {}", KEY_BUILD_ID);
		KEY_CORE_TRACE("Initializing...");
	}

	void ShutdownCore()
	{
		KEY_CORE_TRACE("Shutting down...");
	}

}