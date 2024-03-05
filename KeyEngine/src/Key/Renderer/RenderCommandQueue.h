#pragma once

#include "Kpch.h"

namespace Key {
	class RenderCommandQueue
	{
	public:
		//指向无返回值、参数为 void* 的函数的指针类型
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


