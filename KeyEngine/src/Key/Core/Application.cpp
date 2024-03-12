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
	 * ʹ�� std::bind ������һ����Ա�����İ�.
	 * @param &Application::x Application��Ա������ַ
	 * @param this ָ��ǰApplicationʵ��
	 * @param std::placeholders::_1 һ��ռλ������ʾ�ڵ��ð󶨵ĺ���ʱ�����ݵ�һ������
	 */
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;
	
	/**
	 * @brief Application���캯��.
	 *
	 * ʹ��ApplicationProps��Ϊ��Ϣ����Ӧ�ã�
	 *		�������ڣ�����OnEvent�����󶨵����ڣ���Ϊ����ϵͳ��������¼��Ļص������������¼���Ϊ�������ݸ�OnEvent��
	 *		����Imgui UI��
	 *		��ʼ����Ⱦ����ȷ��Ӧ�ó�������Ⱦ�������п�����������
	 * \param props ����Ӧ�����ƣ����ڴ�С����Ϣ
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
	 * .@brief �����¼��ķַ�
	 * 
	 *	@details  �������¼��ķַ��ʹ��ݸ���Ӧ�Ĵ��������Լ��������¼���Ϊ�������ݸ�ͼ����д���
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
	 * @brief �ı�Ӧ�ô��ں�Ļص�����
	 * 
	 *	�жϴ��ڸı��Ĵ�С�Ƿ�Ϊ0��С������С����ֱ�ӷ����������
	 *	����������Ⱦ�ӿڴ�С����������ÿһ��framebuffer �ߴ�
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
	 * @brief ���ļ��Ի���ѡ���ļ�
	 * ��Ӧ�ó����д��ļ��Ի��򣬲������û�ѡ����ļ���·����
	 * \param filter ָ���ļ����͹��������������û�����ѡ����ļ����͡�
	 * \return 
	 *		@retval ofn.lpstrFile ����ѡ�����ļ���
	 *		@retval std::string() ���ַ���
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
	 * @brief Ӧ�ó������ѭ��.
	 * 
	 * ����Ӧ�ó���������������,������
	 *		����ͼ��ջ������ÿ��ͼ��� OnUpdate ����������ͼ���״̬
	 *		��ȾUI
	 *		�������¼������´��ڵ���ʾ
	 *		����֡ʱ��ͬ��
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

