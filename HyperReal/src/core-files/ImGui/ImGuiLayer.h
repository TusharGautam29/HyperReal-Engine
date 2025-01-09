#pragma once
#include "core-files/Layer.h"
#include "core-files/Event/ApplicationEvent.h"
#include "core-files/Event/MouseEvent.h"
#include "core-files/Event/KeyEvent.h"

#include "C:\HyperReal\HyperReal\HyperReal\thirdparty\imgui\backends\imgui_impl_opengl3.cpp"
#include "C:\HyperReal\HyperReal\HyperReal\thirdparty\imgui\backends\imgui_impl_glfw.cpp"


namespace HyperR {
	class HyperR_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;
		virtual void OnImGuiRender() override;
		void begin();
		void end();
	private:
		float m_Time = 0.0f;

	};
}