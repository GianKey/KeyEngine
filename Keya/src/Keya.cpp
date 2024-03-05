#include <Key.h>
#include <Key/EntryPoint.h>

#include "EditorLayer.h"

class KeyaApplication : public Key::Application
{
public:
    KeyaApplication(const Key::ApplicationProps& props)
        : Application(props)
    {
    }

    virtual void OnInit() override
    {
        PushLayer(new Key::EditorLayer());
    }
};

Key::Application* Key::CreateApplication()
{
    return new KeyaApplication({ "Keya", 1600, 900 });
}
