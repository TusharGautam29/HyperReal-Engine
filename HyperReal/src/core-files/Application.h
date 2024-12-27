#pragma once
#include "core.h"
namespace HyperR
{
	class HyperR_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};
	Application* CreateApplication();
}


