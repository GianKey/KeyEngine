#include "Kpch.h"
#include "RendererContext.h"

#include "Key/Renderer/RendererAPI.h"

#include "Key/Platform/OpenGL/OpenGLContext.h"
#include "Key/Platform/Vulkan/VulkanContext.h"

namespace Key {

	Ref<RendererContext> RendererContext::Create()
	{
		switch (RendererAPI::Current())
		{
			case RendererAPIType::None:    return nullptr;
			case RendererAPIType::OpenGL:  return Ref<OpenGLContext>::Create();
			case RendererAPIType::Vulkan:  return Ref<VulkanContext>::Create();
		}
		KEY_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}