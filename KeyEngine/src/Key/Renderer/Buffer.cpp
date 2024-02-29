#include "Kpch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Key/PlatForm/OpenGL/OpenGLBuffer.h"

namespace Key {
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::RendererAPIType::None:    KEY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::RendererAPIType::OpenGL:  return new OpenGLVertexBuffer(vertices, size);
		}

		KEY_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::RendererAPIType::None:    KEY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::RendererAPIType::OpenGL:  return new OpenGLIndexBuffer(indices, size);
		}

		KEY_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}