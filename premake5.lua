workspace "HyperReal"
	architecture "x64"	
	startproject "Sandbox"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir={}
IncludeDir["GLFW"]="HyperReal/thirdparty/GLFW/include"
IncludeDir["Glad"]="HyperReal/thirdparty/Glad/include"
IncludeDir["ImGui"]="HyperReal/thirdparty/imgui"
IncludeDir["glm"]="HyperReal/thirdparty/glm"
IncludeDir["stb_image"]="HyperReal/thirdparty/stb_image"


group "Dependencies"
	include "HyperReal/thirdparty/GLFW"
	include "HyperReal/thirdparty/Glad"
	include "HyperReal/thirdparty/imgui"

group ""

project "HyperReal"
	location "HyperReal"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "hrpch.h"
	pchsource "HyperReal/src/hrpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/thirdparty/stb_image/**.cpp",
		"%{prj.name}/thirdparty/stb_image/**.h",
		"%{prj.name}/thirdparty/glm/glm/**.hpp",
		"%{prj.name}/thirdparty/glm/glm/**.inl"

	}
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/thirdparty/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}
	links 
	{ 
		"GLFW",	
		"ImGui",	
		"Glad",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"
		defines
		{
			"HR_PLATFORM_WINDOWS",
			"HR_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			"IMGUI_IMPL_OPENGL_LOADER_GLAD"
		}

	filter "configurations:Debug"
		defines "HR_DEBUG"
		runtime "Debug"
		symbols "on"
	filter "configurations:Release"
		defines "HR_RELEASE"
		runtime "Release"
		optimize "on"
	filter "configurations:Dist"
		defines "HR_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	cppdialect "C++17"
	language "C++"
	staticruntime "on"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	includedirs
	{
		"HyperReal/thirdparty/spdlog/include",
		"HyperReal/src",
		"HyperReal/thirdparty",
		"%{IncludeDir.glm}"
	}
	links	
	{
		"HyperReal",
	}

	filter "system:windows"
		
		systemversion "latest"
		defines
		{
			"HR_PLATFORM_WINDOWS"
		}
	filter "configurations:Debug"
		defines "HR_DEBUG"
		runtime "Debug"
		symbols "on"
	filter "configurations:Release"
		defines "HR_RELEASE"
		runtime "Release"
		optimize "on"
	filter "configurations:Dist"
		defines "HR_DIST"
		runtime "Release"
		optimize "on"
