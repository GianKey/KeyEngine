#include "Kpch.h"
#include "Shader.h"
#include "Key/Renderer/Renderer.h"
#include "Key/PlatForm/OpenGL/OpenGLShader.h"
#include "Key/Renderer/RendererAPI.h"
#include <glad/glad.h>

namespace Key {
	Shader* Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    KEY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLShader(filepath);
		}

		KEY_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}


}