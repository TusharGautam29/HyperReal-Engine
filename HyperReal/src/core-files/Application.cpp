#include "hrpch.h"
#include "Application.h"
#include "Event/ApplicationEvent.h"
#include "Log.h"

namespace HyperR
{
	Application::Application()
	{
	}
	Application::~Application()
	{
	}
	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			HR_TRACE("{}", e.ToString());
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			HR_TRACE("{}", e.ToString());
		}

		while (true);
	}
	
}