#pragma once

#include "Key/Core/Base.h"
#include "Key/Core/Events/Event.h"
#include "Key/Core/TimeStep.h"
namespace Key {
	/**
	 * @brief 图层类
	 * 
	 * 用于将不同的功能模块或者抽象层次分离开来，以提高代码的可维护性、可扩展性和可重用性。
	 * 
	 * @note 图层是软件开发中一种常见的组织模式。
	 * 常见的使用场景包括游戏引擎中的图层管理（例如场景图层、UI图层等）、图形应用程序中的渲染层、网络应用程序中的协议层等。
	 * 通过使用图层，可以将复杂的系统分解为更小的、更易于管理和理解的部分，每个部分都有特定的职责和功能。
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