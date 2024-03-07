#include "Kpch.h"
#include "RenderCommandQueue.h"

#define KEY_RENDER_TRACE(...) KEY_CORE_TRACE(__VA_ARGS__)

namespace Key {

	RenderCommandQueue::RenderCommandQueue()
	{
		m_CommandBuffer = new uint8_t[10 * 1024 * 1024]; // 10mb buffer
		m_CommandBufferPtr = m_CommandBuffer;
		// The memset function initializes all bytes in the allocated memory block
		//to zero to ensure that the command buffer in the starting state is empty
		memset(m_CommandBuffer, 0, 10 * 1024 * 1024);
	}

	RenderCommandQueue::~RenderCommandQueue()
	{
		delete[] m_CommandBuffer;
	}

	void* RenderCommandQueue::Allocate(RenderCommandFn fn, uint32_t size)
	{
		// TODO: alignment
		//Write the function pointer fn into the command buffer
		*(RenderCommandFn*)m_CommandBufferPtr = fn;
		m_CommandBufferPtr += sizeof(RenderCommandFn);

		*(uint32_t*)m_CommandBufferPtr = size;
		m_CommandBufferPtr += sizeof(uint32_t);

		void* memory = m_CommandBufferPtr;
		m_CommandBufferPtr += size;

		m_CommandCount++;
		return memory;
	}

	void RenderCommandQueue::Execute()
	{
		//HZ_RENDER_TRACE("RenderCommandQueue::Execute -- {0} commands, {1} bytes", m_CommandCount, (m_CommandBufferPtr - m_CommandBuffer));
		//Back up the starting position of the command buffer: Save the starting address of the command buffer in the buffer variable
		byte* buffer = m_CommandBuffer;

		for (uint32_t i = 0; i < m_CommandCount; i++)
		{
			//Read the rendering command function pointer function from the buffer
			//and call the function to execute the rendering command
			RenderCommandFn function = *(RenderCommandFn*)buffer;
			buffer += sizeof(RenderCommandFn);

			uint32_t size = *(uint32_t*)buffer;
			buffer += sizeof(uint32_t);
			function(buffer);
			//Based on the previously stored rendering command size,
			//move the pointer of the buffer backwards to the position of the next rendering command
			buffer += size;
		}
		//reset command buffer and counter
		m_CommandBufferPtr = m_CommandBuffer;
		m_CommandCount = 0;
	}

}