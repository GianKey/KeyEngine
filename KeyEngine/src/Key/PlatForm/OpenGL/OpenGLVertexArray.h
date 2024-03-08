#pragma once
#include "Key/Renderer/Renderer.h"
#include "Key/Renderer/VertexArray.h"

namespace Key {
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		virtual const std::vector <Ref<VertexBuffer>>& GetVertexBuffer() const override { return m_VertexBuffers; }
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }

		virtual RendererID GetRendererID() const override { return m_RendererID; };
	private:
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
		RendererID m_RendererID = 0;
		uint32_t m_VertexBufferIndex = 0;
	};

}