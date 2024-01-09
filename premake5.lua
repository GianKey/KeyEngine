
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
IncludeDir["GLad"] = "KeyEngine/vendor/GLad/include"
IncludeDir["imGui"] = "KeyEngine/vendor/imgui"
IncludeDir["glm"] = "Hazel/vendor/glm"
include "KeyEngine/vendor/GLFW"
include "KeyEngine/vendor/GLad"
include "KeyEngine/vendor/imgui"

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
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLad}",
		"%{IncludeDir.imGui}",
		"%{IncludeDir.glm}"
	}

	links{
		"GLFW",
		"GLad",
		"ImGui",
		"opengl32.lib"
	}


	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	defines
	{
		"KEY_PLATFORM_WINDOWS",
		"KEY_BUILD_DLL",
		"GLFW_INCLUDE_NONE"
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
		"KeyEngine/src/",
		"KeyEngine/vendor",
		"%{IncludeDir.glm}"
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
		buildoptions "/MDd"

	filter "configurations:Release"
		defines "KE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "KE_DIST"
		optimize "On"

