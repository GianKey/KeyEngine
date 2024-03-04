#pragma once

#include "Base.h"
#include "Key/Core/TimeStep.h"
#include "Window.h"
#include "LayerStack.h"

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "Key/ImGui/ImGuiLayer.h"

namespace Key {
	class KEY_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		//3D
		virtual void OnInit() {}
		virtual void OnShutdown() {}
		virtual void OnUpdate() {}
		void RenderImGui();
		std::string OpenFile(const std::string& filter) const;
		//3D---end
		void OnEvent(Event& e);
		
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	

		inline Window& GetWindow() { return *m_Window; }
		static inline Application& Get() { return *s_Instance; }

		float GetTime() const; // TODO: This should be in "Platform"
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		static Application* s_Instance;

		float m_LastFrameTime = 0.0f;
		
		TimeStep m_TimeStep;
	};

	//Implemented by CLIENT
	Application* CreateApplication();
}


