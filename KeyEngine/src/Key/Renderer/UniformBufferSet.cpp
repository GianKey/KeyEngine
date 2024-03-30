#include "Kpch.h"
#include "UniformBufferSet.h"

#include "Key/Renderer/Renderer.h"

#include "Key/Platform/OpenGL/OpenGLUniformBufferSet.h"
#include "Key/Platform/Vulkan/VulkanUniformBufferSet.h"

#include "Key/Renderer/RendererAPI.h"

namespace Key {

	Ref<UniformBufferSet> UniformBufferSet::Create(uint32_t frames)
	{
		switch (RendererAPI::Current())
		{
			case RendererAPIType::None:     return nullptr;
			case RendererAPIType::Vulkan:  return Ref<VulkanUniformBufferSet>::Create(frames);
			case RendererAPIType::OpenGL:  return Ref<OpenGLUniformBufferSet>::Create(frames);
		}

		KEY_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}