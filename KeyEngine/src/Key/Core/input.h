#pragma once
#include "Base.h"
#include "Kpch.h"

namespace Key {
	class  Input
	{
	public:
		static bool IsKeyPressed(int keycode);

		static bool IsMouseButtonPressed(int button);
		static float GetMouseX();
		static float GetMouseY();
	};
}

