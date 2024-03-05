#include "Kpch.h"
#include "Renderer.h"
#include "Shader.h"
#include "Key/PlatForm/OpenGL/OpenGLShader.h"


namespace Key {

	Renderer* Renderer::s_Instance = new Renderer();
	RendererAPIType RendererAPI::s_CurrentRendererAPI = RendererAPIType::OpenGL;

	void Renderer::Init()
	{
		s_Instance->m_ShaderLibrary = std::make_unique<ShaderLibrary>();
		KEY_RENDER({ RendererAPI::Init(); });

		Renderer::GetShaderLibrary()->Load("assets/shaders/KeyPBR_Static.glsl");
		Renderer::GetShaderLibrary()->Load("assets/shaders/KeyPBR_Anim.glsl");
	}

	void Renderer::Clear()
	{
		KEY_RENDER({
	RendererAPI::Clear(0.0f, 0.0f, 0.0f, 1.0f);
			});
	}
	void Renderer::Clear(float r, float g, float b, float a)
	{
		KEY_RENDER_4(r, g, b, a, {
			RendererAPI::Clear(r, g, b, a);
			});
	}

	void Renderer::ClearMagenta()
	{
		Clear(1, 0, 1);
	}

	void Renderer::SetClearColor(float r, float g, float b, float a)
	{
	}

	void Renderer::DrawIndexed(uint32_t count, bool depthTest)
	{
		KEY_RENDER_2(count, depthTest, {
			RendererAPI::DrawIndexed(count, depthTest);
			});
	}

	void Renderer::WaitAndRender()
	{
		s_Instance->m_CommandQueue.Execute();
	}

}