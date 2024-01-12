#include <Key.h>
#include <Key/Core/TimeStep.h>



class ExampleLayer : public Key::Layer {
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
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

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<Key::VertexBuffer> squareVB;
		squareVB.reset(Key::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Key::ShaderDataType::Float3, "a_Position", false }
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
			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
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

		m_Shader.reset(new Key::Shader(vertexSrc, fragmentSrc));

		std::string blue_vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			uniform mat4 u_ViewProjection;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection *  vec4(a_Position, 1.0);	
			}
		)";

		std::string blue_fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_blueShader.reset(new Key::Shader(blue_vertexSrc, blue_fragmentSrc));

	}


	void OnUpdate(Key::TimeStep  ts) override {

		KEY_TRACE("Delta time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());
		if (Key::Input::IsKeyPressed(KEY_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Key::Input::IsKeyPressed(KEY_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Key::Input::IsKeyPressed(KEY_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		else if (Key::Input::IsKeyPressed(KEY_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;

		if (Key::Input::IsKeyPressed(KEY_KEY_Q))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		else if (Key::Input::IsKeyPressed(KEY_KEY_E))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		Key::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Key::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);
		Key::Renderer::BeginScene(m_Camera);

		Key::Renderer::Submit(m_blueShader, m_SquareVA);

		//m_Shader->Bind();
		//m_Shader->UpLoadUniformMat4("u_ViewProjection", m_Camera.GetViewProjectionMatrix());
		Key::Renderer::Submit(m_Shader, m_VertexArray);

		Key::Renderer::EndScene();

	}

	void OnEvent(Key::Event& event) override {
		if (event.GetEventType() == Key::EventType::KeyPressed)
		{
			Key::KeyPressedEvent& e = dynamic_cast<Key::KeyPressedEvent&>(event);
			KEY_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
private:
	std::shared_ptr<Key::Shader> m_Shader;
	std::shared_ptr<Key::VertexArray> m_VertexArray;

	std::shared_ptr<Key::Shader> m_blueShader;
	std::shared_ptr<Key::VertexArray> m_SquareVA;

	Key::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 1.0f;			//控制相机移动

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 30.0f; //控制相机旋转

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