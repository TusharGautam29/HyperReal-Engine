#pragma once
#ifdef HR_PLATFORM_WINDOWS

extern HyperR::Application* HyperR::CreateApplication();

int main(int argc, char** argv)
{
	HyperR::Log::Init();
	HR_CORE_WARN("Initialised Log");
	std::cout << "Welcome to HyperReal Engine!" << std::endl;
	
	HR_PROFILE_BEGIN_SESSION("Startup", "HyperRealProfile-Startup.json");
	auto app = HyperR::CreateApplication();
	HR_PROFILE_END_SESSION();

	HR_PROFILE_BEGIN_SESSION("Runtime", "HyperRealProfile-Runtime.json");
	app->Run();
	HR_PROFILE_END_SESSION();

	HR_PROFILE_BEGIN_SESSION("Shutdown", "HyperRealProfile-Shutdown.json");
	delete app;
	HR_PROFILE_END_SESSION();

}
#endif