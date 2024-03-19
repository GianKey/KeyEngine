#include "Kpch.h"
#include "Material.h"
#include "Key/Platform/Vulkan/VulkanMaterial.h"
#include "Key/Platform/OpenGL/OpenGLMaterial.h"
#include "Key/Renderer/RendererAPI.h"
	
namespace Key {
	Ref<Material> Material::Create(const Ref<Shader>& shader, const std::string& name)
	{
		switch (RendererAPI::Current())
		{
			case RendererAPIType::None: return nullptr;
			case RendererAPIType::Vulkan: return Ref<VulkanMaterial>::Create(shader, name);
			case RendererAPIType::OpenGL: return Ref<OpenGLMaterial>::Create(shader, name);
		}
		KEY_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}