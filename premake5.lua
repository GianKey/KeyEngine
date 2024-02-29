
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
IncludeDir["glm"] = "KeyEngine/vendor/glm"
IncludeDir["stb_image"] = "KeyEngine/vendor/stb_image"
IncludeDir["assimp"] = "KeyEngine/vendor/assimp/include"

group "Dependencies"
	include "KeyEngine/vendor/GLFW"
	include "KeyEngine/vendor/GLad"
	include "KeyEngine/vendor/imgui"
group ""

project "KeyEngine"
	location "KeyEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir("bin/" ..outputdir.. "/%{prj.name}")
	objdir("bin-int/" ..outputdir.. "/%{prj.name}")

	pchheader "Kpch.h"
	pchsource "KeyEngine/src/Kpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLad}",
		"%{IncludeDir.imGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.assimp}",
	}

	links{
		"GLFW",
		"GLad",
		"ImGui",
		"opengl32.lib"
	}


	filter "system:windows"
		systemversion "latest"

	defines
	{
		"KEY_PLATFORM_WINDOWS",
		"KEY_BUILD_DLL",
		"GLFW_INCLUDE_NONE"
	}

	filter "configurations:Debug"
		defines "KE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "KE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "KE_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"KeyEngine",
		"KeyEngine/vendor/assimp/win64/assimp-vc143-mtd.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"KEY_PLATFORM_WINDOWS"
		}


	filter "configurations:Debug"
		defines "KE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "KE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "KE_DIST"
		runtime "Release"
		optimize "on"

