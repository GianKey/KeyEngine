#pragma once

#include "Key/Renderer/Renderer.h"

#include "Vulkan.h"
#include "VulkanDevice.h"
#include "VulkanAllocator.h"
#include "VulkanSwapChain.h"

struct GLFWwindow;

namespace Key {

	class VulkanContext : public RendererContext
	{
	public:
		VulkanContext();
		virtual ~VulkanContext();

		virtual void Init() override;

		Ref<VulkanDevice> GetDevice() { return m_Device; }
		
		static VkInstance GetInstance() { return s_VulkanInstance; }

		static Ref<VulkanContext> Get() { return Ref<VulkanContext>(Renderer::GetContext()); }
		static Ref<VulkanDevice> GetCurrentDevice() { return Get()->GetDevice(); }
	private:

		// Devices
		Ref<VulkanPhysicalDevice> m_PhysicalDevice;
		Ref<VulkanDevice> m_Device;

		// Vulkan instance
		inline static VkInstance s_VulkanInstance;
		VkDebugReportCallbackEXT m_DebugReportCallback = VK_NULL_HANDLE;
		VkPipelineCache m_PipelineCache = nullptr;

		VulkanAllocator m_Allocator;
		VulkanSwapChain m_SwapChain;
	};
}