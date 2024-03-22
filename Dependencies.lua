
-- Key Dependencies

-- Include directories relative to root folder
VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/KeyEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/KeyEngine/vendor/Glad/include"
IncludeDir["Imgui"] = "%{wks.location}/KeyEngine/vendor/Imgui"
IncludeDir["glm"] = "%{wks.location}/KeyEngine/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/KeyEngine/vendor/stb/include"
IncludeDir["assimp"] = "%{wks.location}/KeyEngine/vendor/assimp/include"
IncludeDir["entt"] = "%{wks.location}/KeyEngine/vendor/entt/include"
IncludeDir["FastNoise"] = "%{wks.location}/KeyEngine/vendor/FastNoise"
IncludeDir["mono"] = "%{wks.location}/KeyEngine/vendor/mono/include"
IncludeDir["Box2D"] = "%{wks.location}/KeyEngine/vendor/Box2D/include"

IncludeDir["yaml_cpp"] = "%{wks.location}/KeyEngine/vendor/yaml-cpp/include"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"
IncludeDir["shaderc"] = "%{IncludeDir.VulkanSDK}/shaderc"
IncludeDir["SPIRV_Cross"] = "%{IncludeDir.VulkanSDK}/spirv_cross"
IncludeDir["NvidiaAftermath"] = "%{wks.location}/KeyEngine/vendor/NvidiaAftermath/include"

LibraryDir = {}
LibraryDir["mono"] = "vendor/mono/lib/Debug/mono-2.0-sgen.lib"
LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"
LibraryDir["VulkanSDK_Debug"] = "%{wks.location}/KeyEngine/vendor/VulkanSDK/1.3.261.1/Lib"
LibraryDir["NvidiaAftermath"] = "%{wks.location}/KeyEngine/vendor/NvidiaAftermath/lib/x64"

Library = {}
Library["mono"] = "%{wks.location}/KeyEngine/vendor/mono/lib/Debug/mono-2.0-sgen.lib"
Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
Library["NvidiaAftermath"] = "%{LibraryDir.NvidiaAftermath}/GFSDK_Aftermath_Lib.x64.lib"

Library["ShaderC_Debug"] = "%{LibraryDir.VulkanSDK}/shaderc_sharedd.lib"
Library["SPIRV_Cross_Debug"] = "%{LibraryDir.VulkanSDK}/spirv-cross-cored.lib"
Library["SPIRV_Cross_GLSL_Debug"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsld.lib"
Library["SPIRV_Tools_Debug"] = "%{LibraryDir.VulkanSDK}/SPIRV-Toolsd.lib"

Library["ShaderC_Release"] = "%{LibraryDir.VulkanSDK}/shaderc_sharedd.lib"
Library["SPIRV_Cross_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-core.lib"
Library["SPIRV_Cross_GLSL_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsl.lib"