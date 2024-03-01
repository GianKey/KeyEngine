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

		void* Allocate(RenderCommandFn func, unsigned int size);

		void Execute();
	private:
		unsigned char* m_CommandBuffer;
		unsigned char* m_CommandBufferPtr;
		unsigned int m_CommandCount = 0;
	};
}


