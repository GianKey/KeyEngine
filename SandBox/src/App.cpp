#include <Key.h>



class ExampleLayer : public Key::Layer {
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override {
		//KEY_INFO("ExampleLayer :: Update");
		if (Key::Input::IsKeyPressed(KEY_KEY_TAB))
			KEY_TRACE("Tab key is pressed!");
	}

	void OnEvent(Key::Event& event) override {
		//KEY_TRACE("{0}", event);
		if (event.GetEventType() == Key::EventType::KeyPressed)
		{
			Key::KeyPressedEvent& e = dynamic_cast<Key::KeyPressedEvent&>(event);
			KEY_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};
class SandBox : public Key::Application {
public:
	SandBox()
	{
		PushLayer(new ExampleLayer());
	}

	~SandBox() {
	}

};


Key::Application* Key::CreateApplication() {
	return new SandBox();
}