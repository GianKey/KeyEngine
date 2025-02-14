#include "Kpch.h"
#include "RenderPass.h"

#include "Renderer.h"

#include "Key/Platform/OpenGL/OpenGLRenderPass.h"
#include "Key/Platform/Vulkan/VulkanRenderPass.h"

#include "Key/Renderer/RendererAPI.h"

namespace Key {

    Ref<RenderPass> RenderPass::Create(const RenderPassSpecification& spec)
    {
        switch (RendererAPI::Current())
        {
            case RendererAPIType::None:    KEY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPIType::Vulkan:  return Ref<VulkanRenderPass>::Create(spec);
            case RendererAPIType::OpenGL:  return Ref<OpenGLRenderPass>::Create(spec);
        }

        KEY_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}