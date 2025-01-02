#pragma once
#include "core.h"
#include "Event/Event.h"
#include "Event/ApplicationEvent.h"
#include "Window.h"	


namespace HyperR
{
	class HyperR_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
	private:

		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};
	Application* CreateApplication();
}


