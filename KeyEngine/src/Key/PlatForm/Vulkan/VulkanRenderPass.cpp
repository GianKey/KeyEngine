#include "Kpch.h"
#include "VulkanRenderPass.h"

namespace Key {

	VulkanRenderPass::VulkanRenderPass(const RenderPassSpecification& spec)
		: m_Specification(spec)
	{
	}

	VulkanRenderPass::~VulkanRenderPass()
	{
	}

}