#include "Kpch.h"
#include "RenderPass.h"

#include "Renderer.h"

#include "Key/Platform/OpenGL/OpenGLRenderPass.h"

namespace Key {

    Ref<RenderPass> RenderPass::Create(const RenderPassSpecification& spec)
    {
        switch (RendererAPI::Current())
        {
        case RendererAPIType::None:    KEY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPIType::OpenGL:  return std::make_shared<OpenGLRenderPass>(spec);
        }

        KEY_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}