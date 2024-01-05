
workspace "KeyEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder
IncludeDir = {}
IncludeDir["GLFW"] = "KeyEngine/vendor/GLFW/include"
include "KeyEngine/vendor/GLFW"

project "KeyEngine"
	location "KeyEngine"
	kind "SharedLib"
	language "C++"

	targetdir("bin/" ..outputdir.. "/%{prj.name}")
	objdir("bin-int/" ..outputdir.. "/%{prj.name}")

	pchheader "Kpch.h"
	pchsource "KeyEngine/src/Kpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links{
		"GLFW",
		"opengl32.lib"
	}


	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	defines
	{
		"KEY_PLATFORM_WINDOWS",
		"KEY_BUILD_DLL"
	}
	postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} ../bin/" ..outputdir.. "/Sandbox")
	}

	filter "configurations:Debug"
		defines "KE_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "KE_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "KE_DIST"
		buildoptions "/MD"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir("bin/" ..outputdir.. "/%{prj.name}")
	objdir("bin-int/" ..outputdir.. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"KeyEngine/vendor/spdlog/include",
		"KeyEngine/src/"
	}

	links
	{
		"KeyEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	defines
	{
		"KEY_PLATFORM_WINDOWS"
	}


	filter "configurations:Debug"
		defines "KE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "KE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "KE_DIST"
		optimize "On"

