#pragma once

#include "Key/Core/Layer.h"
#include "Key/Core/Events/Event.h"
//#include "Key/PlatForm/OpenGL/ImGuiOpenGLRenderer.h"
#include "Key/Core/Events/ApplicationEvent.h"
#include "Key/Core/Events/KeyBoardEvent.h"
#include "Key/Core/Events/MouseEvent.h"

namespace Key {

	class  ImGuiLayer : public Layer
	{
	public:
		virtual void Begin() = 0;
		virtual void End() = 0;

		void SetDarkThemeColors();

		static ImGuiLayer* Create();
	};

}