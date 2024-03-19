#include "Kpch.h"
#include "Texture.h"

#include "RendererAPI.h"
#include "Key/PlatForm/OpenGL/OpenGLTexture.h"
#include "Key/Platform/Vulkan/VulkanTexture.h"

#include "Key/Renderer/RendererAPI.h"
namespace Key {

	Ref<Texture2D> Texture2D::Create(ImageFormat format, uint32_t width, uint32_t height, const void* data) 
	{
		switch (RendererAPI::Current())
		{
			case RendererAPIType::None: return nullptr;
			case RendererAPIType::OpenGL: return Ref<OpenGLTexture2D>::Create(format, width, height, data);
			case RendererAPIType::Vulkan: return Ref<VulkanTexture2D>::Create(format, width, height, data);
		}
		KEY_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path, bool srgb)
	{
		switch (RendererAPI::Current())
		{
			case RendererAPIType::None: return nullptr;
			case RendererAPIType::OpenGL: return Ref<OpenGLTexture2D>::Create(path, srgb);
			case RendererAPIType::Vulkan: return Ref<VulkanTexture2D>::Create(path, srgb);
		}
		KEY_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Ref<TextureCube> TextureCube::Create(ImageFormat format, uint32_t width, uint32_t height, const void* data)
	{
		switch (RendererAPI::Current())
		{
			case RendererAPIType::None: return nullptr;
			case RendererAPIType::OpenGL: return Ref<OpenGLTextureCube>::Create(format, width, height, data);
			case RendererAPIType::Vulkan: return Ref<VulkanTextureCube>::Create(format, width, height, data);
		}
		KEY_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Ref<TextureCube> TextureCube::Create(const std::string& path)
	{
		switch (RendererAPI::Current())
		{
			case RendererAPIType::None: return nullptr;
			case RendererAPIType::OpenGL: return Ref<OpenGLTextureCube>::Create(path);
				//case RendererAPIType::Vulkan: return Ref<VulkanTextureCube>::Create(path);
		}
		KEY_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}