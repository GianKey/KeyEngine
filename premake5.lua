
workspace "KeyEngine"
	architecture "x64"
	targetdir "build"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	startproject "Keya"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder
IncludeDir = {}
IncludeDir["GLFW"] = "KeyEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "KeyEngine/vendor/Glad/include"
IncludeDir["Imgui"] = "KeyEngine/vendor/Imgui"
IncludeDir["glm"] = "KeyEngine/vendor/glm"
IncludeDir["stb_image"] = "KeyEngine/vendor/stb/include"
IncludeDir["assimp"] = "KeyEngine/vendor/assimp/include"
IncludeDir["entt"] = "KeyEngine/vendor/entt/include"
IncludeDir["FastNoise"] = "KeyEngine/vendor/FastNoise"
IncludeDir["mono"] = "KeyEngine/vendor/mono/include"

LibraryDir = {}
LibraryDir["mono"] = "vendor/mono/lib/Debug/mono-2.0-sgen.lib"

group "Dependencies"
include "KeyEngine/vendor/GLFW"
include "KeyEngine/vendor/Glad"
include "KeyEngine/vendor/Imgui"
group ""

group "Core"
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
		"%{prj.name}/src/**.c", 
		"%{prj.name}/src/**.hpp", 
		"%{prj.name}/src/**.cpp",

		"%{prj.name}/vendor/FastNoise/**.cpp"
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.Imgui}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.mono}",
		"%{IncludeDir.FastNoise}",
		"%{prj.name}/vendor/assimp/include",
		"%{IncludeDir.stb_image}",	
	}

	links{
		"GLFW",
		"Glad",
		"Imgui",
		"opengl32.lib",
		"%{LibraryDir.mono}"
	}

	filter "files:KeyEngine/vendor/FastNoise/**.cpp"
		flags { "NoPCH" }


	filter "system:windows"
		systemversion "latest"

		defines
		{
			"KEY_PLATFORM_WINDOWS",
			"KEY_BUILD_DLL",
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

project "Key-ScriptCore"
	location "Key-ScriptCore"
	kind "SharedLib"
	language "C#"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.cs", 
	}
group ""

group "Tools"
project "Keya"
		location "Keya"
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++17"
		staticruntime "on"
	
		targetdir("bin/" ..outputdir.. "/%{prj.name}")
		objdir("bin-int/" ..outputdir.. "/%{prj.name}")
	
		links
		{
			"KeyEngine"
		}
		
		files 
		{ 
			"%{prj.name}/src/**.h", 
			"%{prj.name}/src/**.c", 
			"%{prj.name}/src/**.hpp", 
			"%{prj.name}/src/**.cpp" 
		}

		includedirs
		{
			"%{prj.name}/src",
			"KeyEngine/src/",
			"KeyEngine/vendor",
			"%{IncludeDir.entt}",
			"%{IncludeDir.glm}"
		}
	

		postbuildcommands 
		{
			'{COPY} "../Keya/assets" "%{cfg.targetdir}/assets"'
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

			links
			{
				"KeyEngine/vendor/assimp/win64/assimp-vc143-mtd.lib"
			}
			postbuildcommands 
			{
				'{COPY} "../KeyEngine/vendor/assimp/win64/assimp-vc143-mtd.dll" "%{cfg.targetdir}"',
				'{COPY} "../KeyEngine/vendor/mono/bin/Debug/mono-2.0-sgen.dll" "%{cfg.targetdir}"'
			}
	
		filter "configurations:Release"
			defines "KE_RELEASE"
			runtime "Release"
			optimize "on"
			links
			{
				"KeyEngine/vendor/assimp/win64/assimp-vc143-mtd.lib"
			}
			postbuildcommands 
			{
				'{COPY} "../KeyEngine/vendor/assimp/win64/assimp-vc143-mt.dll" "%{cfg.targetdir}"',
				'{COPY} "../KeyEngine/vendor/mono/bin/Debug/mono-2.0-sgen.dll" "%{cfg.targetdir}"'
			}
	
		filter "configurations:Dist"
			defines "KE_DIST"
			runtime "Release"
			optimize "on"
			links
			{
				"KeyEngine/vendor/assimp/win64/assimp-vc143-mtd.lib"
			}
			postbuildcommands 
			{
				'{COPY} "../KeyEngine/vendor/assimp/win64/assimp-vc143-mtd.dll" "%{cfg.targetdir}"',
				'{COPY} "../KeyEngine/vendor/mono/bin/Debug/mono-2.0-sgen.dll" "%{cfg.targetdir}"'
			}
	
	group ""

group "Examples"
project "ExampleApp"
	location "ExampleApp"
	kind "SharedLib"
	language "C#"

	targetdir ("Keya/assets/scripts")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.cs", 
	}

	links
	{
		"Key-ScriptCore"
	}

--[[project "Sandbox"
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

--]]
group ""