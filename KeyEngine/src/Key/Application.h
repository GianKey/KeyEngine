#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Key/ImGui/ImGuiLayer.h"
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/OrthographicCamera.h"
namespace Key {
	class KEY_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		Window& GetWindow() { return *m_Window; }
		static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;

		LayerStack m_LayerStack;
		static Application* s_Instance;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<Shader> m_blueShader;
		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<VertexArray> m_SquareVA;
		
		OrthographicCamera m_Camera;
	};
	Application* CreateApplication();
}


