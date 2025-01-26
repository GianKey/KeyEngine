#include "Kpch.h"
#include "RenderCommandQueue.h"

#define KEY_RENDER_TRACE(...) KEY_CORE_TRACE(__VA_ARGS__)

namespace Key {

	/**
	 * @brief RenderCommandQueue类的构造函数.
	 * 
	 * 主要作用是初始化RenderCommandQueue类的实例，为渲染命令缓冲区分配内存，
	 * 并将其初始化为一个空的状态，准备接收新的渲染命令。
	 * 
	 */
	RenderCommandQueue::RenderCommandQueue()
	{
		///动态分配了一个大小为10MB的内存块，并将其地址赋值给m_CommandBuffer成员变量。这个内存块被用作渲染命令缓冲区。
		m_CommandBuffer = new uint8_t[10 * 1024 * 1024]; // 10mb buffer
		m_CommandBufferPtr = m_CommandBuffer;
		///使用memset函数将分配的内存块中的所有字节初始化为零。
		/// 这确保了在初始化时，渲染命令缓冲区处于空状态，没有任何残留的数据。
		memset(m_CommandBuffer, 0, 10 * 1024 * 1024);
	}

	RenderCommandQueue::~RenderCommandQueue()
	{
		delete[] m_CommandBuffer;
	}

	/**
	 * @brief 用于向渲染命令队列中分配内存，并将函数指针和命令大小写入命令缓冲区。
	 * 
	 * \param fn 一个函数指针参数，它指向一个没有返回值且参数为void*的函数。在渲染命令队列中，这个函数指针用于指定要执行的渲染命令。
	 * \param size 表示要分配的内存空间的大小。这个大小用于确定将要写入到命令缓冲区中的命令的大小，以便后续可以正确地执行这些命令。
	 * \return memory 返回分配的内存空间的起始地址。
	 * 
	 * @note ODO: alignmen，在写入函数指针和命令大小之前，需要考虑对齐的问题。
	 * 对齐是指确保数据存储在内存中的合适位置，通常是以特定的字节边界为单位。
	 * 涉及到确保写入的数据按照某种规定的对齐方式进行存储，以提高数据访问的效率和性能。
	 */
	void* RenderCommandQueue::Allocate(RenderCommandFn fn, uint32_t size)
	{
		// TODO: alignment
		///将函数指针 fn 写入到当前命令缓冲区指针 m_CommandBufferPtr 指向的位置
		*(RenderCommandFn*)m_CommandBufferPtr = fn;
		m_CommandBufferPtr += sizeof(RenderCommandFn);

		///将命令的大小写入到当前命令缓冲区指针 m_CommandBufferPtr 指向的位置
		*(uint32_t*)m_CommandBufferPtr = size;
		m_CommandBufferPtr += sizeof(uint32_t);

		///将当前命令缓冲区指针指向的位置赋给 memory 变量，这个位置存储了即将分配的内存空间的起始地址。
		void* memory = m_CommandBufferPtr;
		//将参数调用的渲染fun的大小写入，给外部submit来的参数fun预留空间
		m_CommandBufferPtr += size;

		m_CommandCount++;
		return memory;
	}

	/**
	 * @brief 用于执行存储在渲染命令队列中的所有命令。
	 * 
	 * 执行命令队列中的所有命令，并在执行完毕后将状态重置为初始状态，以便下一轮命令的执行。
	 * 渲染指令读取基于Allocate中为每个指令分配的各个信息大小的空间
	 * 读取执行的实际上是renderCmd(Func)这个函数
	 */
	void RenderCommandQueue::Execute()
	{
		//KEY_RENDER_TRACE("RenderCommandQueue::Execute -- {0} commands, {1} bytes", m_CommandCount, (m_CommandBufferPtr - m_CommandBuffer));
		/////备份命令缓冲区起始位置：将命令缓冲区的起始地址保存在缓冲区变量中
		byte* buffer = m_CommandBuffer;

		for (uint32_t i = 0; i < m_CommandCount; i++)
		{
			///从缓冲区读取渲染命令函数指针函数
			///并调用函数来执行渲染命令
			RenderCommandFn function = *(RenderCommandFn*)buffer;
			buffer += sizeof(RenderCommandFn);

			uint32_t size = *(uint32_t*)buffer;
			buffer += sizeof(uint32_t);
			//将buffer当前所指的函数地址，作为参数
			function(buffer);
			///基于先前存储的渲染命令大小，
			///将缓冲区的指针向后移动到下一个渲染命令的位置
			buffer += size;
		}
		///重置命令缓冲区和计数器
		m_CommandBufferPtr = m_CommandBuffer;
		m_CommandCount = 0;
	}

}