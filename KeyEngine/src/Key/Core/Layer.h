#pragma once

#include "Key/Core/Base.h"
#include "Key/Core/Events/Event.h"
#include "Key/Core/TimeStep.h"
namespace Key {

	class KEY_API Layer
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