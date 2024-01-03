
workspace "KeyEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

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
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src"
	}
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0"

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
		symbols "On"

	filter "configurations:Release"
		defines "KE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "KE_DIST"
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
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0"

	links
	{
		"KeyEngine"
	}

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

