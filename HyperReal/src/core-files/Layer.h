#pragma once

#include "core.h"
#include "Event/Event.h"

namespace HyperR {
	class HyperR_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();
		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}
		inline const std::string& GetName() const { return m_DebugName; }
		virtual void OnImGuiRender() {}
	protected:
		std::string m_DebugName;
	};
}