#pragma once

#ifdef KEY_PLATFORM_WINDOWS

extern Key::Application* Key::CreateApplication();


int main(int argc, char** argv) {
	Key::InitializeCore();
	KEY_CORE_ERROR("create a key app");
	int a = 7;
	KEY_INFO("��� key master, ���� {0}", a);

	auto app = Key::CreateApplication();
	app->Run();
	delete app;
	Key::ShutdownCore();
}
#endif // KEY_PALTFORM_WINDOWS