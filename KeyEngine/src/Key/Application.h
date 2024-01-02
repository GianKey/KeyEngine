#pragma once

#include "Core.h"
#include "Events/Event.h"
namespace Key {
	class KEY_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	
	};
	Application* CreateApplication();
}


