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
		ImGuiLayer();
		ImGuiLayer(const std::string& name);
		virtual ~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

		void SetDarkThemeColors();
	private:
		float m_Time = 0;
	};

}