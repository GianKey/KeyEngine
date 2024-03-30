#include "Kpch.h"
#include "RenderCommandBuffer.h"

#include "Key/Platform/Vulkan/VulkanRenderCommandBuffer.h"

#include "Key/Renderer/RendererAPI.h"

namespace Key {

	Ref<RenderCommandBuffer> RenderCommandBuffer::Create(uint32_t count)
	{
		switch (RendererAPI::Current())
		{
			case RendererAPIType::None:    return nullptr;
			case RendererAPIType::Vulkan:  return Ref<VulkanRenderCommandBuffer>::Create(count);
		}
		KEY_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}