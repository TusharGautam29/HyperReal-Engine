#include <HyperReal.h>
#include "core-files/Core/EntryPoint.h"

#include "Sandbox2D.h"
#include "ExampleLayer.h"



class sandbox : public HyperR::Application
{
public:
	sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
		
	}
	~sandbox()
	{
	}
};
HyperR::Application* HyperR::CreateApplication()
{
	return new sandbox();
}