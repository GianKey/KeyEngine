#include "Kpch.h"
#include "VertexArray.h"
#include "Key/Renderer/Renderer.h"
#include "Key/PlatForm/OpenGL/OpenGLVertexArray.h"

namespace Key {

	VertexArray* VertexArray::Create() {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:		KEY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return new OpenGLVertexArray();
		}

		KEY_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}