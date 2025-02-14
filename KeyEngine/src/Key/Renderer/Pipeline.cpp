#include "Kpch.h"
#include "Pipeline.h"

#include "Renderer.h"

#include "Key/Platform/OpenGL/OpenGLPipeline.h"
#include "Key/Platform/Vulkan/VulkanPipeline.h"

#include "Key/Renderer/RendererAPI.h"

namespace Key {

	Ref<Pipeline> Pipeline::Create(const PipelineSpecification& spec)
	{
		switch (RendererAPI::Current())
		{
			case RendererAPIType::None:    return nullptr;
			case RendererAPIType::OpenGL:  return Ref<OpenGLPipeline>::Create(spec);
			case RendererAPIType::Vulkan:  return Ref<VulkanPipeline>::Create(spec);
		}
		KEY_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}