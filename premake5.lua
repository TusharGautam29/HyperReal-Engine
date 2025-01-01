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

include "HyperReal/thirdparty/GLFW"



project "HyperReal"
	location "HyperReal"
	kind "SharedLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "hrpch.h"
	pchsource "HyperReal/src/hrpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/thirdparty/spdlog/include",
		"%{IncludeDir.GLFW}"
	}
	links 
	{ 
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.19041.0"
		defines
		{
			"HR_PLATFORM_WINDOWS",
			"HR_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPYDIR} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "HR_DEBUG"
		symbols "On"
	filter "configurations:Release"
		defines "HR_RELEASE"
		optimize "On"
	filter "configurations:Dist"
		defines "HR_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
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
	}
	links	
	{
		"HyperReal",
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.19041.0"
		defines
		{
			"HR_PLATFORM_WINDOWS"
		}
	filter "configurations:Debug"
		defines "HR_DEBUG"
		symbols "On"
	filter "configurations:Release"
		defines "HR_RELEASE"
		optimize "On"
	filter "configurations:Dist"
		defines "HR_DIST"
		optimize "On"
