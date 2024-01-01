#include <Key.h>


class SandBox : public Key::Application {
public:
	SandBox()
	{

	}

	~SandBox() {
	}

};


Key::Application* Key::CreateApplication() {
	return new SandBox();
}