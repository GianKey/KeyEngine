#include "Kpch.h"
#include "UniformBuffer.h"

#include "Key/Renderer/Renderer.h"

#include "Key/Platform/OpenGL/OpenGLUniformBuffer.h"
#include "Key/Platform/Vulkan/VulkanUniformBuffer.h"

#include "Key/Renderer/RendererAPI.h"

namespace Key {

	Ref<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
	{
		switch (RendererAPI::Current())
		{
			case RendererAPIType::None:     return nullptr;
			case RendererAPIType::Vulkan:  return Ref<VulkanUniformBuffer>::Create(size, binding);
			case RendererAPIType::OpenGL:  return Ref<OpenGLUniformBuffer>::Create(size, binding);
		}

		KEY_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
