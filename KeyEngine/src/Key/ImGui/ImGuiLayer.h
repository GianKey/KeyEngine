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
		virtual void OnEvent(Event& e) override;
		virtual void OnUpdate() override;

		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
	private:
		float m_Time = 0;
	};

}