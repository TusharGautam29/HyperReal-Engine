#pragma once

#include "core.h"
#include "core-files/Event/Event.h"
#include "core-files/Core/Timestep.h"

namespace HyperR {
	class HyperR_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();
		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnEvent(Event& event) {}
		inline const std::string& GetName() const { return m_DebugName; }
		virtual void OnImGuiRender() {}
	protected:
		std::string m_DebugName;
	};
}