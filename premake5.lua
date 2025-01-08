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


group "Dependencies"
	include "HyperReal/thirdparty/GLFW"
	include "HyperReal/thirdparty/Glad"
	include "HyperReal/thirdparty/imgui"

group ""

project "HyperReal"
	location "HyperReal"
	kind "SharedLib"
	language "C++"
	staticruntime "off"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "hrpch.h"
	pchsource "HyperReal/src/hrpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
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
		"%{IncludeDir.glm}"
	}
	links 
	{ 
		"GLFW",	
		"ImGui",	
		"Glad",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "10.0.19041.0"
		defines
		{
			"HR_PLATFORM_WINDOWS",
			"HR_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			"IMGUI_IMPL_OPENGL_LOADER_GLAD"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "HR_DEBUG"
		runtime "Debug"
		symbols "On"
	filter "configurations:Release"
		defines "HR_RELEASE"
		runtime "Release"
		optimize "On"
	filter "configurations:Dist"
		defines "HR_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"
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
		"%{IncludeDir.glm}"
	}
	links	
	{
		"HyperReal",
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "10.0.19041.0"
		defines
		{
			"HR_PLATFORM_WINDOWS"
		}
	filter "configurations:Debug"
		defines "HR_DEBUG"
		runtime "Debug"
		symbols "On"
	filter "configurations:Release"
		defines "HR_RELEASE"
		runtime "Release"
		optimize "On"
	filter "configurations:Dist"
		defines "HR_DIST"
		runtime "Release"
		optimize "On"
