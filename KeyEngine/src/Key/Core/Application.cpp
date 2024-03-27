#include "Kpch.h"
#include "Application.h"

#include "Key/Renderer/Renderer.h"
#include "Key/Renderer/Framebuffer.h"
#include <GLFW/glfw3.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <Windows.h>
#include "Key/Platform/Vulkan/VulkanRenderer.h"
#include "Key/Platform/Vulkan/VulkanAllocator.h"
#include "Key/Script/ScriptEngine.h"
#include "Key/Asset/AssetManager.h"
#include <imgui/imgui.h>
#include "imgui/imgui_internal.h"

extern bool g_ApplicationRunning;
extern ImGuiContext* GImGui;

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

		m_Profiler = new PerformanceProfiler();

		m_Window = std::unique_ptr<Window>(Window::Create(WindowProps(props.Name, props.WindowWidth, props.WindowHeight)));
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		m_Window->Maximize();
		m_Window->SetVSync(true);

		// Init renderer and execute command queue to compile all shaders
		Renderer::Init();
		Renderer::WaitAndRender();

		m_ImGuiLayer = ImGuiLayer::Create();
		PushOverlay(m_ImGuiLayer);

		ScriptEngine::Init("assets/scripts/ExampleApp.dll");

		AssetManager::Init();
	}
	Application::~Application() 
	{
		for (Layer* layer : m_LayerStack)
		{
			layer->OnDetach();
			delete layer;
		}

		FramebufferPool::GetGlobal()->GetAll().clear();
		ScriptEngine::Shutdown();

		AssetManager::Shutdown();
		Renderer::WaitAndRender();
		Renderer::Shutdown();

		delete m_Profiler;
		m_Profiler = nullptr;
	}

	/**
	 * @callgraph
	 * .@brief �����¼��ķַ�
	 * 
	 *	@details  �������¼��ķַ��ʹ��ݸ���Ӧ�Ĵ��������Լ��������¼���Ϊ�������ݸ�ͼ����д���
	 * 
	 * \parame
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

		m_Window->GetRenderContext()->OnResize(width, height);

		auto& fbs = FramebufferPool::GetGlobal()->GetAll();
		for (auto& fb : fbs)
		{
			if (!fb->GetSpecification().NoResize)
				fb->Resize(width, height);
		}
		return false;
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		g_ApplicationRunning = false; // Request close
		return true;
	}

	void Application::RenderImGui()
	{
		m_ImGuiLayer->Begin();

		ImGui::Begin("Renderer");
		auto& caps = Renderer::GetCapabilities();
		ImGui::Text("Vendor: %s", caps.Vendor.c_str());
		ImGui::Text("Renderer: %s", caps.Device.c_str());
		ImGui::Text("Version: %s", caps.Version.c_str());
		ImGui::Separator();
		ImGui::Text("Frame Time: %.2fms\n", m_TimeStep.GetMilliseconds());

		if (RendererAPI::Current() == RendererAPIType::Vulkan)
		{
			GPUMemoryStats memoryStats = VulkanAllocator::GetStats();
			std::string used = Utils::BytesToString(memoryStats.Used);
			std::string free = Utils::BytesToString(memoryStats.Free);
			ImGui::Text("Used VRAM: %s", used.c_str());
			ImGui::Text("Free VRAM: %s", free.c_str());
		}

		ImGui::End();

		ImGui::Begin("Performance");
		ImGui::Text("Frame Time: %.2fms\n", m_TimeStep.GetMilliseconds());
		const auto& perFrameData = m_Profiler->GetPerFrameData();
		for (auto&& [name, time] : perFrameData)
		{
			ImGui::Text("%s: %.3fms\n", name, time);
		}

		ImGui::End();
		m_Profiler->Clear();

		for (Layer* layer : m_LayerStack)
			layer->OnImGuiRender();

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

	const char* Application::GetConfigurationName()
	{
#if defined(KEY_DEBUG)
		return "Debug";
#elif defined(KEY_RELEASE)
		return "Release";
#elif defined(KEY_DIST)
		return "Dist";
#else
	#error Undefined configuration?
#endif
	}

	const char* Application::GetPlatformName()
	{
#if defined(KEY_PLATFORM_WINDOWS)
		return "Windows x64";
#else
	#error Undefined platform?
#endif
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
			static uint64_t frameCounter = 0;
			//KEY_CORE_INFO("-- BEGIN FRAME {0}", frameCounter);
			m_Window->ProcessEvents();

			if (!m_Minimized)
			{
				Renderer::BeginFrame();
				//VulkanRenderer::BeginFrame();

				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(m_TimeStep);

					// Render ImGui on render threads
				Application* app = this;
				Renderer::Submit([app]() { app->RenderImGui(); });
				Renderer::Submit([=]() {m_ImGuiLayer->End(); });
				Renderer::EndFrame();

				// On Render thread
				m_Window->GetRenderContext()->BeginFrame();
				//Update render command address
				Renderer::WaitAndRender();
				m_Window->SwapBuffers();
			}

			float time = GetTime(); //Platform GetTime()
			m_TimeStep = time - m_LastFrameTime;
			m_LastFrameTime = time;


			//KEY_CORE_INFO("-- END FRAME {0}", frameCounter);
			frameCounter++;
		}
		OnShutdown();
	}

	void Application::Close()
	{
		m_Running = false;
	}


}

