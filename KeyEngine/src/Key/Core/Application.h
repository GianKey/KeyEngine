#pragma once

#include "Base.h"
#include "Key/Core/TimeStep.h"
#include "Window.h"
#include "LayerStack.h"

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "Key/ImGui/ImGuiLayer.h"

namespace Key {
	
	/**
	 * @struct ApplicationProps
	 * @brief 应用程序的基本信息
	 * 用于创建初始化应用
	 */
	struct ApplicationProps {
		std::string Name;
		uint32_t WindowWidth, WindowHeight;
	};

	/**
	 * @brief 应用类
	 * 
	 * 前端使用引擎源码执行功能的类
	 */
	class  Application
	{
	public:
		Application(const ApplicationProps& props = { "KeyEngine", 1280, 720 });
		virtual ~Application();

		void Run();
		void Close();
	
		virtual void OnInit() {}
		virtual void OnShutdown() {}
		virtual void OnUpdate() {}
		void RenderImGui();
		std::string OpenFile(const char* filter = "All\0*.*\0") const;
		std::string SaveFile(const char* filter = "All\0*.*\0") const;

		void OnEvent(Event& e);
		
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	

		inline Window& GetWindow() { return *m_Window; }
		static inline Application& Get() { return *s_Instance; }

		float GetTime() const; // TODO: This should be in "Platform"

		static const char* GetConfigurationName();
		static const char* GetPlatformName();
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
	Application* CreateApplication(int argc, char** argv);
}


