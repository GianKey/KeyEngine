#pragma once

#include "Kpch.h"

/**
 * @brief. RenderCommandQueue
 */
namespace Key {
	class RenderCommandQueue
	{
	public:
	
		////Pointer type to a function with no return value and parameter void *
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


