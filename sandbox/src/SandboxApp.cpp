#include <HyperReal.h>

class ExampleLayer : public HyperR::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}
	void OnUpdate() override
	{
		HR_INFO("ExampleLayer::Update");
	}
	void OnEvent(HyperR::Event& event) override
	{
		HR_TRACE("{0}", event);
	}
};

class sandbox : public HyperR::Application
{
public:
	sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~sandbox()
	{
	}
};
HyperR::Application* HyperR::CreateApplication()
{
	return new sandbox();
}