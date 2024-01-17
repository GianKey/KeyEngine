#include <Key.h>
#include <Key/Core/TimeStep.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Key/PlatForm/OpenGL/OpenGLShader.h"
#include "Key/Renderer/CameraController.h"
class ExampleLayer : public Key::Layer {
public:
	ExampleLayer()
		//: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f), m_SquarePosition(0.0f)
		: Layer("Example"), m_CameraController(1600.0f / 900.0f)
	{
		m_VertexArray.reset(Key::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.3f, 0.8f, 0.0f, 1.0f
		};

		std::shared_ptr<Key::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Key::VertexBuffer::Create(vertices, sizeof(vertices)));


		Key::BufferLayout layout = {
			{ Key::ShaderDataType::Float3, "a_Position", false},
			{ Key::ShaderDataType::Float4, "a_Color", false}
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);


		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Key::IndexBuffer> indexBuffer;
		indexBuffer.reset(Key::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Key::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.75f, -0.75f, 0.0f,0.0f, 0.0f,
			 0.75f, -0.75f, 0.0f,1.0f, 0.0f,
			 0.75f,  0.75f, 0.0f,1.0f, 1.0f,
			-0.75f,  0.75f, 0.0f,0.0f, 1.0f,
		};


		std::shared_ptr<Key::VertexBuffer> squareVB;
		squareVB.reset(Key::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Key::ShaderDataType::Float3, "a_Position", false },
			{ Key::ShaderDataType::Float2, "a_TexCoord", false },
			});
		m_SquareVA->AddVertexBuffer(squareVB);


		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Key::IndexBuffer> squareIB;
		squareIB.reset(Key::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection *  u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = v_Color;
			}
		)";
	

		
		auto FlatShader = m_ShaderLibrary.Load("assets/Shaders/FlatColor.glsl");

	
		//m_TextureShader.reset(Key::Shader::Create(texturevertexSrc, texturefragmentSrc));
		auto textureShader = m_ShaderLibrary.Load("assets/Shaders/Texture.glsl");
		m_Texture = Key::Texture2D::Create("assets/textures/Checkerboard.png");
		m_logoTexture = Key::Texture2D::Create("assets/textures/ChernoLogo.png");
		std::dynamic_pointer_cast<Key::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Key::OpenGLShader>(textureShader)->UpLoadUniformInt("u_Texture", 0);

	}


	void OnUpdate(Key::TimeStep  ts) override {
		Key::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Key::RenderCommand::Clear();

		//KEY_TRACE("Delta time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());
		m_CameraController.OnUpdate(ts);


		
		/*m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);*/
		Key::Renderer::BeginScene(m_CameraController.GetCamera());

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.06f));
		glm::vec4 redColor(0.8f, 0.2f, 0.3f, 1.0f);
		glm::vec4 blueColor(0.2f, 0.3f, 0.8f, 1.0f);

		std::dynamic_pointer_cast<Key::OpenGLShader>(m_ShaderLibrary.Get("FlatColor"))->Bind();

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				if (x % 2 == 0)
					std::dynamic_pointer_cast<Key::OpenGLShader>(m_ShaderLibrary.Get("FlatColor"))->UpLoadUniformFloat4("u_Color", m_FlatColor);
				else
					std::dynamic_pointer_cast<Key::OpenGLShader>(m_ShaderLibrary.Get("FlatColor"))->UpLoadUniformFloat4("u_Color", blueColor);

				Key::Renderer::Submit(m_ShaderLibrary.Get("FlatColor"), m_SquareVA, transform);
			}
		}
		//glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_SquarePosition);
		//Key::Renderer::Submit(m_blueShader, m_SquareVA, transform);

		//Key::Renderer::Submit(m_Shader, m_VertexArray);
		m_Texture->Bind();
		Key::Renderer::Submit(m_ShaderLibrary.Get("Texture"), m_SquareVA);
		m_logoTexture->Bind();
		Key::Renderer::Submit(m_ShaderLibrary.Get("Texture"), m_SquareVA);
			//glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		Key::Renderer::EndScene();

	}

	void OnEvent(Key::Event& event) override {
		if (event.GetEventType() == Key::EventType::KeyPressed)
		{
			Key::KeyPressedEvent& e = dynamic_cast<Key::KeyPressedEvent&>(event);
			KEY_TRACE("{0}", (char)e.GetKeyCode());


		}
		
		m_CameraController.OnEvent(event);
	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Flat Color", glm::value_ptr(m_FlatColor));

		ImGui::End();
	}
private:
	std::shared_ptr<Key::Shader> m_Shader;
	std::shared_ptr<Key::VertexArray> m_VertexArray;

	std::shared_ptr<Key::Shader> m_FlatColorShader;
	std::shared_ptr<Key::VertexArray> m_SquareVA;

	std::shared_ptr<Key::Shader> m_TextureShader;
	Key::ShaderLibrary m_ShaderLibrary;
	std::shared_ptr<Key::VertexArray> m_TXSquareVA;

	//Key::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 1.0f;			//控制相机移动

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 30.0f; //控制相机旋转

	std::shared_ptr<Key::Texture2D> m_Texture,m_logoTexture;

	glm::vec3 m_SquarePosition; 
	glm::vec4 m_FlatColor;


	Key::OrthographicCameraController m_CameraController;

};
class SandBox : public Key::Application {
public:
	SandBox() :Application()
	{
		PushLayer(new ExampleLayer());
	}

	~SandBox() {
	}

};


Key::Application* Key::CreateApplication() {
	return new SandBox();
}