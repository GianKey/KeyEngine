#include "Kpch.h"
#include "Texture.h"

#include "RendererAPI.h"
#include "Key/PlatForm/OpenGL/OpenGLTexture.h"
#include "Key/Platform/Vulkan/VulkanTexture.h"

#include "Key/Renderer/RendererAPI.h"
namespace Key {

	Ref<Texture2D> Texture2D::Create(ImageFormat format, uint32_t width, uint32_t height, const void* data, TextureProperties properties)
	{
		switch (RendererAPI::Current())
		{
			case RendererAPIType::None: return nullptr;
			case RendererAPIType::OpenGL: return Ref<OpenGLTexture2D>::Create(format, width, height, data, properties);
			case RendererAPIType::Vulkan: return Ref<VulkanTexture2D>::Create(format, width, height, data, properties);
		}
		KEY_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path, TextureProperties properties)
	{
		switch (RendererAPI::Current())
		{
			case RendererAPIType::None: return nullptr;
			case RendererAPIType::OpenGL: return Ref<OpenGLTexture2D>::Create(path, properties);
			case RendererAPIType::Vulkan: return Ref<VulkanTexture2D>::Create(path, properties);
		}
		KEY_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Ref<TextureCube> TextureCube::Create(ImageFormat format, uint32_t width, uint32_t height, const void* data, TextureProperties properties)
	{
		switch (RendererAPI::Current())
		{
			case RendererAPIType::None: return nullptr;
			case RendererAPIType::OpenGL: return Ref<OpenGLTextureCube>::Create(format, width, height, data, properties);
			case RendererAPIType::Vulkan: return Ref<VulkanTextureCube>::Create(format, width, height, data, properties);
		}
		KEY_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Ref<TextureCube> TextureCube::Create(const std::string& path, TextureProperties properties)
	{
		switch (RendererAPI::Current())
		{
			case RendererAPIType::None: return nullptr;
			case RendererAPIType::OpenGL: return Ref<OpenGLTextureCube>::Create(path, properties);
			case RendererAPIType::Vulkan: return Ref<VulkanTextureCube>::Create(path, properties);
		}
		KEY_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}