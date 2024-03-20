
workspace "KeyEngine"
	architecture "x64"
	targetdir "build"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}
	
	startproject "Keya"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Dependencies.lua"

group "Dependencies"
include "KeyEngine/vendor/GLFW"
include "KeyEngine/vendor/Glad"
include "KeyEngine/vendor/Imgui"
include "KeyEngine/vendor/Box2D"
group ""

group "Core"
project "KeyEngine"
	location "KeyEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

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

		"%{prj.name}/vendor/FastNoise/**.cpp",

		"%{prj.name}/vendor/yaml-cpp/src/**.cpp",
		"%{prj.name}/vendor/yaml-cpp/src/**.h",
		"%{prj.name}/vendor/yaml-cpp/include/**.h",
		"%{prj.name}/vendor/VulkanMemoryAllocator/**.h",
        "%{prj.name}/vendor/VulkanMemoryAllocator/**.cpp"
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor",
		"%{IncludeDir.assimp}",
        "%{IncludeDir.stb}",
        "%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.Imgui}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.mono}",
		"%{IncludeDir.FastNoise}",
		"%{IncludeDir.VulkanSDK}",
		"%{IncludeDir.stb_image}",	
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.Box2D}",
		"%{IncludeDir.NvidiaAftermath}",
	}

	links{
		"GLFW",
		"Glad",
		"Imgui",
		"Box2D",
		"opengl32.lib",
		"%{Library.Vulkan}",

		"%{Library.mono}",
		"%{Library.NvidiaAftermath}",
	}

	filter "files:KeyEngine/vendor/FastNoise/**.cpp or files:KeyEngine/vendor/yaml-cpp/src/**.cpp"
		flags { "NoPCH" }


	filter "system:windows"
		systemversion "latest"

		defines
		{
			"KEY_PLATFORM_WINDOWS",
			"KEY_BUILD_DLL",
		}

	filter "configurations:Debug"
		defines "KEY_DEBUG"
		runtime "Debug"
		symbols "on"

		links
        {
            "%{Library.ShaderC_Debug}",
            "%{Library.SPIRV_Cross_Debug}",
            "%{Library.SPIRV_Cross_GLSL_Debug}",
			"%{Library.SPIRV_Tools_Debug}",
        }


	filter "configurations:Release"
		defines "KEY_RELEASE"
		runtime "Release"
		optimize "on"

		links
        {
            "%{Library.ShaderC_Release}",
            "%{Library.SPIRV_Cross_Release}",
            "%{Library.SPIRV_Cross_GLSL_Release}",
        }


	filter "configurations:Dist"
		defines "KEY_DIST"
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
		staticruntime "off"
	
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
			"%{IncludeDir.glm}", 
			"%{IncludeDir.ImGui}",
			"%{IncludeDir.Vulkan}",
			"%{IncludeDir.Glad}"
		}
	

		postbuildcommands 
		{
			'{COPY} "../KeyEngine/vendor/NvidiaAftermath/lib/x64/GFSDK_Aftermath_Lib.x64.dll" "%{cfg.targetdir}"'
		}
	
		filter "system:windows"
			systemversion "latest"
	
			defines
			{
				"KEY_PLATFORM_WINDOWS"
			}
	
	
		filter "configurations:Debug"
			defines "KEY_DEBUG"
			runtime "Debug"
			symbols "on"

			links
			{
				"KeyEngine/vendor/assimp/win64/assimp-vc143-mtd.lib"
			}
			postbuildcommands 
			{
				'{COPY} "../KeyEngine/vendor/assimp/win64/assimp-vc143-mtd.dll" "%{cfg.targetdir}"',
				'{COPY} "../KeyEngine/vendor/mono/bin/Debug/mono-2.0-sgen.dll" "%{cfg.targetdir}"',
				'{COPY} "%{VULKAN_SDK}/Bin/shaderc_sharedd.dll" "%{cfg.targetdir}"'
			}
	
		filter "configurations:Release"
			defines "KEY_RELEASE"
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
			defines "KEY_DIST"
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

workspace "Sandbox"
	architecture "x64"
	targetdir "build"
	
	configurations 
	{ 
		"Debug", 
		"Release",
		"Dist"
	}

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
    staticruntime "off"

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
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.Vulkan}",
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