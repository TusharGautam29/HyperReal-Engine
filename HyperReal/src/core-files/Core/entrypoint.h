#pragma once
#ifdef HR_PLATFORM_WINDOWS

extern HyperR::Application* HyperR::CreateApplication();

int main(int argc, char** argv)
{
	HyperR::Log::Init();
	HR_CORE_WARN("Initialised Log");
	int a = 10;
	HR_INFO("Hello! {0}", a);
	std::cout << "Welcome to HyperReal Engine!" << std::endl;
	auto app = HyperR::CreateApplication();
	app->Run();
	delete app;
}
#endif