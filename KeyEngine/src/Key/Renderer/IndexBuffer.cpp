#include "Kpch.h"
#include "IndexBuffer.h"

#include "Renderer.h"

#include "Key/Platform/OpenGL/OpenGLIndexBuffer.h"
#include "Key/Platform/Vulkan/VulkanIndexBuffer.h"

#include "Key/Renderer/RendererAPI.h"
namespace Key {

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t size)
	{
		switch (RendererAPI::Current())
		{
			case RendererAPIType::None:    return nullptr;
			case RendererAPIType::OpenGL:  return Ref<OpenGLIndexBuffer>::Create(size);
			case RendererAPIType::Vulkan:  return Ref<VulkanIndexBuffer>::Create(size);
		}
		KEY_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(void* data, uint32_t size)
	{
		switch (RendererAPI::Current())
		{
			case RendererAPIType::None:    return nullptr;
			case RendererAPIType::OpenGL:  return Ref<OpenGLIndexBuffer>::Create(data, size);
			case RendererAPIType::Vulkan:  return Ref<VulkanIndexBuffer>::Create(data, size);
		}
		KEY_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}