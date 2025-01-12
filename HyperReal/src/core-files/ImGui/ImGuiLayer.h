#pragma once
#include "core-files/Layer.h"
#include "core-files/Event/ApplicationEvent.h"
#include "core-files/Event/MouseEvent.h"
#include "core-files/Event/KeyEvent.h"

namespace HyperR {
	class HyperR_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		void Begin();
		void End();
		bool s_ImGuiInitialized = false;
	private:
		float m_Time = 0.0f;

	};
}