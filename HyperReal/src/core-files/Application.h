#pragma once
#include "core.h"
#include "Event/Event.h"
#include "Event/ApplicationEvent.h"
#include "Window.h"	
#include "LayerStack.h"
#include "core-files/ImGui/ImGuiLayer.h"

namespace HyperR
{
	class HyperR_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		inline Window& GetWindow() { return *m_Window; }
		
		inline static Application& Get() { return *s_Instance; }
	
	private:

		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
	
	private:
		static Application* s_Instance;
	};
	Application* CreateApplication();
}


