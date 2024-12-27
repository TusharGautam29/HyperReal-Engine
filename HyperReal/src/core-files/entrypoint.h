#pragma once
#ifdef HR_PLATFORM_WINDOWS

extern HyperR::Application* HyperR::CreateApplication();

int main(int argc, char** argv)
{
	std::cout << "Welcome to HyperReal Engine!" << std::endl;
	auto app = HyperR::CreateApplication();
	app->Run();
	delete app;
}
#endif