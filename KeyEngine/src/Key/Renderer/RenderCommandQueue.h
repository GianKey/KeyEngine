#pragma once

#include "Kpch.h"

/**
 * @brief. RenderCommandQueue���࣬���ڹ�����Ⱦ�������
 * 
 * �������ҪĿ�����ṩһ�ֻ��ƣ�ʹ����Ⱦ�����������������н��й����ִ�С�
 * �������Ⱦ������ʹ����ͨ��Allocate������ӵ������У�Ȼ��ͨ������Execute���������ִ����Щ���
 * 
 */
namespace Key {
	class RenderCommandQueue
	{
	public:
		///ָ��û�з���ֵ�Ҳ���Ϊvoid�ĺ�����ָ������*
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


