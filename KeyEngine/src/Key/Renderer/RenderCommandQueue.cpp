#include "Kpch.h"
#include "RenderCommandQueue.h"

#define KEY_RENDER_TRACE(...) KEY_CORE_TRACE(__VA_ARGS__)

namespace Key {

	/**
	 * @brief RenderCommandQueue��Ĺ��캯��.
	 * 
	 * ��Ҫ�����ǳ�ʼ��RenderCommandQueue���ʵ����Ϊ��Ⱦ������������ڴ棬
	 * �������ʼ��Ϊһ���յ�״̬��׼�������µ���Ⱦ���
	 * 
	 */
	RenderCommandQueue::RenderCommandQueue()
	{
		///��̬������һ����СΪ10MB���ڴ�飬�������ַ��ֵ��m_CommandBuffer��Ա����������ڴ�鱻������Ⱦ���������
		m_CommandBuffer = new uint8_t[10 * 1024 * 1024]; // 10mb buffer
		m_CommandBufferPtr = m_CommandBuffer;
		///ʹ��memset������������ڴ���е������ֽڳ�ʼ��Ϊ�㡣
		/// ��ȷ�����ڳ�ʼ��ʱ����Ⱦ����������ڿ�״̬��û���κβ��������ݡ�
		memset(m_CommandBuffer, 0, 10 * 1024 * 1024);
	}

	RenderCommandQueue::~RenderCommandQueue()
	{
		delete[] m_CommandBuffer;
	}

	/**
	 * @brief ��������Ⱦ��������з����ڴ棬��������ָ��������Сд�����������
	 * 
	 * \param fn һ������ָ���������ָ��һ��û�з���ֵ�Ҳ���Ϊvoid*�ĺ���������Ⱦ��������У��������ָ������ָ��Ҫִ�е���Ⱦ���
	 * \param size ��ʾҪ������ڴ�ռ�Ĵ�С�������С����ȷ����Ҫд�뵽��������е�����Ĵ�С���Ա����������ȷ��ִ����Щ���
	 * \return memory ���ط�����ڴ�ռ����ʼ��ַ��
	 * 
	 * @note ODO: alignmen����д�뺯��ָ��������С֮ǰ����Ҫ���Ƕ�������⡣
	 * ������ָȷ�����ݴ洢���ڴ��еĺ���λ�ã�ͨ�������ض����ֽڱ߽�Ϊ��λ��
	 * �漰��ȷ��д������ݰ���ĳ�ֹ涨�Ķ��뷽ʽ���д洢����������ݷ��ʵ�Ч�ʺ����ܡ�
	 */
	void* RenderCommandQueue::Allocate(RenderCommandFn fn, uint32_t size)
	{
		// TODO: alignment
		///������ָ�� fn д�뵽��ǰ�������ָ�� m_CommandBufferPtr ָ���λ��
		*(RenderCommandFn*)m_CommandBufferPtr = fn;
		m_CommandBufferPtr += sizeof(RenderCommandFn);

		///������Ĵ�Сд�뵽��ǰ�������ָ�� m_CommandBufferPtr ָ���λ��
		*(uint32_t*)m_CommandBufferPtr = size;
		m_CommandBufferPtr += sizeof(uint32_t);

		///����ǰ�������ָ��ָ���λ�ø��� memory ���������λ�ô洢�˼���������ڴ�ռ����ʼ��ַ��
		void* memory = m_CommandBufferPtr;
		//���������õ���Ⱦfun�Ĵ�Сд�룬���ⲿsubmit���Ĳ���funԤ���ռ�
		m_CommandBufferPtr += size;

		m_CommandCount++;
		return memory;
	}

	/**
	 * @brief ����ִ�д洢����Ⱦ��������е��������
	 * 
	 * ִ����������е������������ִ����Ϻ�״̬����Ϊ��ʼ״̬���Ա���һ�������ִ�С�
	 * ��Ⱦָ���ȡ����Allocate��Ϊÿ��ָ�����ĸ�����Ϣ��С�Ŀռ�
	 * ��ȡִ�е�ʵ������renderCmd(Func)�������
	 */
	void RenderCommandQueue::Execute()
	{
		//KEY_RENDER_TRACE("RenderCommandQueue::Execute -- {0} commands, {1} bytes", m_CommandCount, (m_CommandBufferPtr - m_CommandBuffer));
		/////�������������ʼλ�ã��������������ʼ��ַ�����ڻ�����������
		byte* buffer = m_CommandBuffer;

		for (uint32_t i = 0; i < m_CommandCount; i++)
		{
			///�ӻ�������ȡ��Ⱦ�����ָ�뺯��
			///�����ú�����ִ����Ⱦ����
			RenderCommandFn function = *(RenderCommandFn*)buffer;
			buffer += sizeof(RenderCommandFn);

			uint32_t size = *(uint32_t*)buffer;
			buffer += sizeof(uint32_t);
			//��buffer��ǰ��ָ�ĺ�����ַ����Ϊ����
			function(buffer);
			///������ǰ�洢����Ⱦ�����С��
			///����������ָ������ƶ�����һ����Ⱦ�����λ��
			buffer += size;
		}
		///������������ͼ�����
		m_CommandBufferPtr = m_CommandBuffer;
		m_CommandCount = 0;
	}

}