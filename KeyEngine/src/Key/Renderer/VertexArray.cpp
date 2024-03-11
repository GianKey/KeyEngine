#include "Kpch.h"
#include "VertexArray.h"
#include "Key/Renderer/Renderer.h"
#include "Key/PlatForm/OpenGL/OpenGLVertexArray.h"

namespace Key {

	Ref<VertexArray> VertexArray::Create() {
		switch (RendererAPI::Current())
		{
			case RendererAPIType::None:    KEY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPIType::OpenGL:  return Ref<OpenGLVertexArray>::Create();
		}

		KEY_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}