#pragma once
#include "Key/Core/Base.h"
#include "Layer.h"

#include <vector>

namespace Key {

	/**
	 * @brief 图层栈类.
	 * 
	 * 管理图层的生命周期和渲染顺序。可以轻松地添加、移除和管理图层，从而实现灵活的图层管理。
	 */
	class  LayerStack
	{
	public:
		LayerStack() ;
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
		//std::vector<Layer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		//std::vector<Layer*>::reverse_iterator rend() { return m_Layers.rend(); }
	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0;
	};

}