#include "Application.h"
#include "Log.h"
#include "Events/ApplicationEvent.h"
namespace Key {
	
	Application::Application() {
	
	}
	Application::~Application() {
	
	}

	void Application::Run() {
		Key::WindowResizeEvent e(1200, 720);
		KEY_TRACE(e);
		while (true);
	}

}

