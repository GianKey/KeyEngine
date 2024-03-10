#pragma once

#include "Kpch.h"

/**
 * @brief. RenderCommandQueue的类，用于管理渲染命令队列
 * 
 * 该类的主要目的是提供一种机制，使得渲染命令可以在命令队列中进行管理和执行。
 * 具体的渲染命令由使用者通过Allocate方法添加到队列中，然后通过调用Execute方法来逐个执行这些命令。
 * 
 */
namespace Key {
	class RenderCommandQueue
	{
	public:
		///指向没有返回值且参数为void的函数的指针类型*
		typedef void(*RenderCommandFn) (void*);

		RenderCommandQueue();
		~RenderCommandQueue();

		void* Allocate(RenderCommandFn func, uint32_t size);

		void Execute();
	private:
		uint8_t* m_CommandBuffer;
		uint8_t* m_CommandBufferPtr;
		uint32_t m_CommandCount = 0;
	};
}


