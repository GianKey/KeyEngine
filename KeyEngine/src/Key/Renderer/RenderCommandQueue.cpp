#include "Kpch.h"
#include "RenderCommandQueue.h"

#define KEY_RENDER_TRACE(...) KEY_CORE_TRACE(__VA_ARGS__)

namespace Key {

	RenderCommandQueue::RenderCommandQueue()
	{
		m_CommandBuffer = new unsigned char[10 * 1024 * 1024]; // 10mb buffer
		m_CommandBufferPtr = m_CommandBuffer;
		// memset ������������ڴ���е������ֽڳ�ʼ��Ϊ�㣬��ȷ����ʼ״̬�µ���������ǿյ�
		memset(m_CommandBuffer, 0, 10 * 1024 * 1024);
	}

	RenderCommandQueue::~RenderCommandQueue()
	{
		delete[] m_CommandBuffer;
	}

	void* RenderCommandQueue::Allocate(RenderCommandFn fn, unsigned int size)
	{
		// TODO: alignment
		//������ָ�� fn д�����������
		*(RenderCommandFn*)m_CommandBufferPtr = fn;
		m_CommandBufferPtr += sizeof(RenderCommandFn);

		*(int*)m_CommandBufferPtr = size;
		m_CommandBufferPtr += sizeof(unsigned int);

		void* memory = m_CommandBufferPtr;
		m_CommandBufferPtr += size;

		m_CommandCount++;
		return memory;
	}

	void RenderCommandQueue::Execute()
	{
		//HZ_RENDER_TRACE("RenderCommandQueue::Execute -- {0} commands, {1} bytes", m_CommandCount, (m_CommandBufferPtr - m_CommandBuffer));
		//���������������ʼλ�ã��������������ʼ��ַ������ buffer ������
		byte* buffer = m_CommandBuffer;

		for (unsigned int i = 0; i < m_CommandCount; i++)
		{
			//�� buffer �ж�ȡ��Ⱦ�����ָ�� function�������øú�����ִ����Ⱦ����
			RenderCommandFn function = *(RenderCommandFn*)buffer;
			buffer += sizeof(RenderCommandFn);

			unsigned int size = *(unsigned int*)buffer;
			buffer += sizeof(unsigned int);
			function(buffer);
			//����֮ǰ�洢����Ⱦ�����С���� buffer ��ָ������ƶ�����һ����Ⱦ�����λ��
			buffer += size;
		}
		//������������ͼ�����
		m_CommandBufferPtr = m_CommandBuffer;
		m_CommandCount = 0;
	}

}