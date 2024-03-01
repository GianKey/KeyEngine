#include "Kpch.h"
#include "Texture.h"
#include "Renderer.h"
#include "RendererAPI.h"
#include "Key/PlatForm/OpenGL/OpenGLTexture.h"
namespace Key {
	//Ref<Texture2D> Texture2D::Create(const std::string& path)
	//{
	//	switch (Renderer::GetAPI())
	//	{
	//	case RendererAPIType::None:    KEY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
	//	case RendererAPIType::OpenGL:  return std::make_shared<OpenGLTexture2D>(path);
	//	}

	//	KEY_CORE_ASSERT(false, "Unknown RendererAPI!");
	//	return nullptr;
	//}

	//3D
	Texture2D*  Texture2D::Create(TextureFormat format, unsigned int width, unsigned int height, TextureWrap wrap)
	{
		switch (RendererAPI::Current())
		{
		case RendererAPIType::None: return nullptr;
		case RendererAPIType::OpenGL: return new OpenGLTexture2D(format, width, height, wrap);
		}
		return nullptr;
	}

	Texture2D*  Texture2D::Create(const std::string& path, bool srgb)
	{
		switch (RendererAPI::Current())
		{
		case RendererAPIType::None: return nullptr;
		case RendererAPIType::OpenGL: return new OpenGLTexture2D(path, srgb);
			//Texture2D* ----new OpenGLTexture2D
		}
		return nullptr;
	}

	TextureCube*  TextureCube::Create(const std::string& path)
	{
		switch (RendererAPI::Current())
		{
		case RendererAPIType::None: return nullptr;
		case RendererAPIType::OpenGL: return new OpenGLTextureCube(path);
		}
		return nullptr;
	}

	uint32_t Texture::GetBPP(TextureFormat format)
	{
		switch (format)
		{
		case TextureFormat::RGB:    return 3;
		case TextureFormat::RGBA:   return 4;
		}
		return 0;
	}
	//3D
}