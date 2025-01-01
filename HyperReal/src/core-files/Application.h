#pragma once
#include "core.h"
#include "Event/Event.h"
#include "Window.h"	
namespace HyperR
{
	class HyperR_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};
	Application* CreateApplication();
}


