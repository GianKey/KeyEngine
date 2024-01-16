#include "Kpch.h"
#include "Texture.h"
#include "Renderer.h"
#include "RendererAPI.h"
#include "Key/PlatForm/OpenGL/OpenGLTexture.h"
namespace Key {
	std::shared_ptr<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    KEY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLTexture2D>(path);
		}

		KEY_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}