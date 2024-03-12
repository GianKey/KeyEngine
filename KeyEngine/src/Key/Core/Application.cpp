#include "Kpch.h"
#include "Application.h"

#include "Key/Renderer/Renderer.h"
#include "Key/Renderer/Framebuffer.h"
#include <GLFW/glfw3.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <Windows.h>

#include "Key/Script/ScriptEngine.h"
#include <imgui/imgui.h>

namespace Key {
	/**
	 * 使用 std::bind 来创建一个成员函数的绑定.
	 * @param &Application::x Application成员函数地址
	 * @param this 指向当前Application实例
	 * @param std::placeholders::_1 一个占位符，表示在调用绑定的函数时，传递第一个参数
	 */
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;
	
	/**
	 * @brief Application构造函数.
	 *
	 * 使用ApplicationProps作为信息创建应用：
	 *		创建窗口，并将OnEvent函数绑定到窗口，作为窗口系统处理这个事件的回调函数（窗口事件作为参数传递给OnEvent）
	 *		创建Imgui UI层
	 *		初始化渲染器，确保应用程序在渲染上下文中可以正常工作
	 * \param props 包含应用名称，窗口大小的信息
	 */
	Application::Application(const ApplicationProps& props)
	{
		KEY_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create(WindowProps(props.Name, props.WindowWidth, props.WindowHeight)));
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		m_Window->SetVSync(true);

		m_ImGuiLayer = new ImGuiLayer("ImGui");
		PushOverlay(m_ImGuiLayer);

		ScriptEngine::Init("assets/scripts/ExampleApp.dll");

		Renderer::Init();
		Renderer::WaitAndRender();
	}
	Application::~Application() {
		ScriptEngine::Shutdown();
	}

	/**
	 * @callgraph
	 * .@brief 负责事件的分发
	 * 
	 *	@details  负责处理事件的分发和传递给对应的处理函数，以及将各个事件作为参数传递给图层进行处理。
	 * 
	 * \param e
	 * @ref Event.h
	 * @ref ApplicationEvent.h
	 * 
	 * 
	 */
	void Application::OnEvent(Event& e) {
		
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));
		//KEY_CORE_TRACE("{0}", e);
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}  

	/**
	 * @brief 改变应用窗口后的回调函数
	 * 
	 *	判断窗口改变后的大小是否为0最小化，最小化后直接返回提高性能
	 *	重新设置渲染视口大小并重新设置每一个framebuffer 尺寸
	 * 
	 * \param e
	 * \return 
	 */
	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		int width = e.GetWidth(), height = e.GetHeight();
		if (width == 0 || height == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		//Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		//
		Renderer::Submit([=]() { glViewport(0, 0, width, height); });
		auto& fbs = FramebufferPool::GetGlobal()->GetAll();
		for (auto& fb : fbs)
			fb->Resize(width, height);
		return false;
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	void Application::RenderImGui()
	{
		m_ImGuiLayer->Begin();

		ImGui::Begin("Renderer");
		auto& caps = RendererAPI::GetCapabilities();
		ImGui::Text("Vendor: %s", caps.Vendor.c_str());
		ImGui::Text("Renderer: %s", caps.Renderer.c_str());
		ImGui::Text("Version: %s", caps.Version.c_str());
		ImGui::Text("Frame Time: %.2fms\n", m_TimeStep.GetMilliseconds());
		ImGui::End();

		for (Layer* layer : m_LayerStack)
			layer->OnImGuiRender();

		m_ImGuiLayer->End();
	}

	/**
	 * @brief 打开文件对话框选择文件
	 * 在应用程序中打开文件对话框，并返回用户选择的文件的路径。
	 * \param filter 指定文件类型过滤器，以限制用户可以选择的文件类型。
	 * \return 
	 *		@retval ofn.lpstrFile 返回选定的文件名
	 *		@retval std::string() 空字符串
	 */
	std::string Application::OpenFile(const char* filter) const
	{
		OPENFILENAMEA ofn;       // common dialog box structure
		CHAR szFile[260] = { 0 };       // if using TCHAR macros

		// Initialize OPENFILENAME
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)m_Window->GetNativeWindow());
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = filter;
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

		if (GetOpenFileNameA(&ofn) == TRUE)
		{
			return ofn.lpstrFile;
		}
		return std::string();
	}

	std::string Application::SaveFile(const char* filter) const
	{
		OPENFILENAMEA ofn;       // common dialog box structure
		CHAR szFile[260] = { 0 };       // if using TCHAR macros

		// Initialize OPENFILENAME
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)m_Window->GetNativeWindow());
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = filter;
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

		if (GetSaveFileNameA(&ofn) == TRUE)
		{
			return ofn.lpstrFile;
		}
		return std::string();
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	float Application::GetTime() const
	{
		return (float)glfwGetTime();
	}

	/**
	 * @brief 应用程序的主循环.
	 * 
	 * 负责应用程序的整体控制流程,包括：
	 *		遍历图层栈，调用每个图层的 OnUpdate 函数来更新图层的状态
	 *		渲染UI
	 *		处理窗口事件并更新窗口的显示
	 *		保存帧时间同步
	 */
	void Application::Run() {
		/*Key::WindowResizeEvent e(1200, 720);
		KEY_TRACE(e);*/
		OnInit();
		while (m_Running)
		{
			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(m_TimeStep);

				// Render ImGui on render thread
				/*m_ImGuiLayer->Begin();
				for (Layer* layer : m_LayerStack)
					layer->OnImGuiRender();*/
				/*m_ImGuiLayer->End();*/
				///End imgui

					// Render ImGui on render thread
				Application* app = this;
				Renderer::Submit([app]() { app->RenderImGui(); });

				//Update render command address
				Renderer::WaitAndRender();
			}

			m_Window->OnUpdate();
			float time = GetTime(); //Platform GetTime()
			m_TimeStep = time - m_LastFrameTime;
			m_LastFrameTime = time;
		}
		OnShutdown();
	}



}

