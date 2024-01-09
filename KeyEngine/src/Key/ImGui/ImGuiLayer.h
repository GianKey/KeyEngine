#pragma once

#include "Key/Layer.h"
#include "Key/Events/Event.h"
//#include "Key/PlatForm/OpenGL/ImGuiOpenGLRenderer.h"
#include "Key/Events/ApplicationEvent.h"
#include "Key/Events/KeyBoardEvent.h"
#include "Key/Events/MouseEvent.h"

namespace Key {

	class KEY_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0;
	};

}