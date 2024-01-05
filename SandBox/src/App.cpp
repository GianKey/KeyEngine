#include <Key.h>

class ExampleLayer : public Key::Layer {
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override {
		KEY_INFO("ExampleLayer :: Update");
	}

	void OnEvent(Key::Event& event) override {
		KEY_TRACE("{0}", event);
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