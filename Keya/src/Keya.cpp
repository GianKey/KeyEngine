#include <Key.h>
#include <Key/EntryPoint.h>

#include "EditorLayer.h"

class KeynutApplication : public Key::Application
{
public:
    KeynutApplication(const Key::ApplicationProps& props)
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
    return new KeynutApplication({ "Keynut", 1600, 900 });
}
