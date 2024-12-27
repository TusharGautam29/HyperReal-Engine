#include <HyperReal.h>
class sandbox : public HyperR::Application
{
public:
	sandbox()
	{
	}
	~sandbox()
	{
	}
};
HyperR::Application* HyperR::CreateApplication()
{
	return new sandbox();
}