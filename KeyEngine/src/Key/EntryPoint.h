#pragma once

#ifdef KEY_PLATFORM_WINDOWS

extern Key::Application* Key::CreateApplication(int argc, char** argv);
bool g_ApplicationRunning = true;


int main(int argc, char** argv) {
    while (g_ApplicationRunning)
    {
        Key::InitializeCore();
        Key::Application* app = Key::CreateApplication(argc, argv);
        KEY_CORE_ASSERT(app, "Client Application is null!");
        app->Run();
        delete app;
        Key::ShutdownCore();
    }
}
#endif // KEY_PALTFORM_WINDOWS