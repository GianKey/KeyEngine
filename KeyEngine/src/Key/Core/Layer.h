#pragma once

#include "Key/Core/Base.h"
#include "Key/Core/Events/Event.h"
#include "Key/Core/TimeStep.h"
namespace Key {
	/**
	 * @brief ͼ����
	 * 
	 * ���ڽ���ͬ�Ĺ���ģ����߳����η��뿪��������ߴ���Ŀ�ά���ԡ�����չ�ԺͿ������ԡ�
	 * 
	 * @note ͼ�������������һ�ֳ�������֯ģʽ��
	 * ������ʹ�ó���������Ϸ�����е�ͼ��������糡��ͼ�㡢UIͼ��ȣ���ͼ��Ӧ�ó����е���Ⱦ�㡢����Ӧ�ó����е�Э���ȡ�
	 * ͨ��ʹ��ͼ�㣬���Խ����ӵ�ϵͳ�ֽ�Ϊ��С�ġ������ڹ�������Ĳ��֣�ÿ�����ֶ����ض���ְ��͹��ܡ�
	 */
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(TimeStep ts) {}
		virtual void OnEvent(Event& event) {}
		virtual void OnImGuiRender() {}
		const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}