#pragma once

#include "Key/Renderer/IndexBuffer.h"

#include "Key/Core/Buffer.h"

#include "VulkanAllocator.h"

namespace Key {

	class VulkanIndexBuffer : public IndexBuffer
	{
	public:
		VulkanIndexBuffer(uint32_t size);
		VulkanIndexBuffer(void* data, uint32_t size = 0);
		virtual ~VulkanIndexBuffer();

		virtual void SetData(void* buffer, uint32_t size, uint32_t offset = 0) override;
		virtual void Bind() const override;

		virtual uint32_t GetCount() const override { return m_Size / sizeof(uint32_t); }

		virtual uint32_t GetSize() const override { return m_Size; }
		virtual RendererID GetRendererID() const override;

		VkBuffer GetVulkanBuffer() { return m_VulkanBuffer; }
	private:
		uint32_t m_Size = 0;
		Buffer m_LocalData;

		VkBuffer m_VulkanBuffer = nullptr;
		VmaAllocation m_MemoryAllocation;
	};

}