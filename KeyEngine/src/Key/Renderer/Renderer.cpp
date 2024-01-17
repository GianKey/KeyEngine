#include "Kpch.h"
#include "Renderer.h"
#include "Key/PlatForm/OpenGL/OpenGLShader.h"


namespace Key {
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;
	void Renderer::Init()
	{
		RenderCommand::Init();
	}
	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}
	void Renderer::EndScene()
	{
	}
	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4 transform)
	{
		//在OpenGL 中 Bind 顺序不分先后
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UpLoadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UpLoadUniformMat4("u_Transform", transform);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

}