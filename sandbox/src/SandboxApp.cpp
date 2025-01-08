#include <HyperReal.h>
#include <core-files/ImGui/ImGuiLayer.h>

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
		if (HyperR::Input::IsKeyPressed(HR_KEY_TAB))
		{
			HR_INFO("Tab key is pressed");
		}
	}
	void OnEvent(HyperR::Event& event) override
	{
		//HR_TRACE("{0}", event);
		if (event.GetEventType() == HyperR::EventType::KeyPressed)
		{
			HyperR::KeyPressedEvent& e = (HyperR::KeyPressedEvent&)event;
			HR_TRACE("{0}", (char)e.GetKeyCode());
		}

	}
};

class sandbox : public HyperR::Application
{
public:
	sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new HyperR::ImGuiLayer());
	}
	~sandbox()
	{
	}
};
HyperR::Application* HyperR::CreateApplication()
{
	return new sandbox();
}