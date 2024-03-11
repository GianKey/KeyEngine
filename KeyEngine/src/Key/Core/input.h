#pragma once
#include "Base.h"
#include "Kpch.h"
#include "KeyCodes.h"
namespace Key {
	class  Input
	{
	public:
		static bool IsKeyPressed(KeyCode keycode);

		static bool IsMouseButtonPressed(int button);
		static float GetMouseX();
		static float GetMouseY();
		static std::pair<float, float> GetMousePosition();
	};
}

