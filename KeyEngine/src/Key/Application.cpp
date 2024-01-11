#include "Kpch.h"
#include "Application.h"
#include "Key/input.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
namespace Key {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Key::ShaderDataType::Float:		return GL_FLOAT;
		case Key::ShaderDataType::Float2:		return GL_FLOAT;
		case Key::ShaderDataType::Float3:		return GL_FLOAT;
		case Key::ShaderDataType::Float4:		return GL_FLOAT;
		case Key::ShaderDataType::Mat3:		return GL_FLOAT;
		case Key::ShaderDataType::Mat4:		return GL_FLOAT;
		case Key::ShaderDataType::Int:		return GL_INT;
		case Key::ShaderDataType::Int2:		return GL_INT;
		case Key::ShaderDataType::Int3:		return GL_INT;
		case Key::ShaderDataType::Int4:		return GL_INT;
		case Key::ShaderDataType::Bool:		return GL_BOOL;
		}

		KEY_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}
	
	Application::Application() {

		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		//Vertex Array
		//Vertex Buffer
		//Index Buffer
		//Shader
	
		//������������
		float vertices[3 * 7] = {									//һ���� 3 �����㣬ÿ�������������ԣ��߸�����ֵ���
		-0.5f,-0.5f,0.0f,	1.0f,0.0f,0.0f,1.0f,	//ǰ���� float ������λ�ã�֮���ĸ��������Ӧ��ɫ
		 0.5f,-0.5f,0.0f,	0.0f,1.0f,0.0f,1.0f,
		 0.0f, 0.5f,0.0f,	0.0f,0.0f,1.0f,1.0f,

		};

		glGenVertexArrays(1, &m_VertexArray);		//�������� VertexArray
		glBindVertexArray(m_VertexArray);

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		{
			BufferLayout layout = {
				{ ShaderDataType::Float3, "a_Position", false},
				{ ShaderDataType::Float4, "a_Color", false}
			};

			m_VertexBuffer->SetLayout(layout);
		}


		uint32_t index = 0;
		const auto& layout = m_VertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}

		uint32_t indices[3] = { 0, 1, 2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		std::string VertexSrc = R"(
			#version 410 core
			
			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
			)";
		std::string FragmentSrc = R"(
			#version 410 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
			)";

		m_Shader.reset(new Shader(VertexSrc, FragmentSrc));

	}
	Application::~Application() {
	
	}

	void Application::OnEvent(Event& e) {
		

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		//KEY_CORE_TRACE("{0}", e);
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}


	void Application::Run() {
		/*Key::WindowResizeEvent e(1200, 720);
		KEY_TRACE(e);*/

		while (m_Running)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr); //ʹ�ö���������������ΪDrawElements
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}



}

