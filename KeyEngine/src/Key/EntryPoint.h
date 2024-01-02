#pragma once

#ifdef KEY_PLATFORM_WINDOWS

extern Key::Application* Key::CreateApplication();

 
int main(int argc, char** argv) {
	Key::Log::Init();
	KEY_CORE_ERROR("create a key app");
	int a = 7;
	KEY_INFO("ÄãºÃ key master, ÎÒÊÇ {0}", a);
	auto app = Key::CreateApplication();
	app->Run();
	delete app;
}
#endif // KEY_PALTFORM_WINDOWS