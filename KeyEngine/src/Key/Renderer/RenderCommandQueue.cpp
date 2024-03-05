#include "Kpch.h"
#include "RenderCommandQueue.h"

#define KEY_RENDER_TRACE(...) KEY_CORE_TRACE(__VA_ARGS__)

namespace Key {

	RenderCommandQueue::RenderCommandQueue()
	{
		m_CommandBuffer = new uint8_t[10 * 1024 * 1024]; // 10mb buffer
		m_CommandBufferPtr = m_CommandBuffer;
		// memset 函数将分配的内存块中的所有字节初始化为零，以确保起始状态下的命令缓冲区是空的
		memset(m_CommandBuffer, 0, 10 * 1024 * 1024);
	}

	RenderCommandQueue::~RenderCommandQueue()
	{
		delete[] m_CommandBuffer;
	}

	void* RenderCommandQueue::Allocate(RenderCommandFn fn, uint32_t size)
	{
		// TODO: alignment
		//将函数指针 fn 写入命令缓冲区中
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
		//备份命令缓冲区的起始位置：将命令缓冲区的起始地址保存在 buffer 变量中
		byte* buffer = m_CommandBuffer;

		for (uint32_t i = 0; i < m_CommandCount; i++)
		{
			//从 buffer 中读取渲染命令函数指针 function，并调用该函数来执行渲染命令
			RenderCommandFn function = *(RenderCommandFn*)buffer;
			buffer += sizeof(RenderCommandFn);

			uint32_t size = *(uint32_t*)buffer;
			buffer += sizeof(uint32_t);
			function(buffer);
			//根据之前存储的渲染命令大小，将 buffer 的指针向后移动到下一个渲染命令的位置
			buffer += size;
		}
		//重置命令缓冲区和计数器
		m_CommandBufferPtr = m_CommandBuffer;
		m_CommandCount = 0;
	}

}