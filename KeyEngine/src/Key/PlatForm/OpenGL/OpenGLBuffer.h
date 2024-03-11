#pragma once
#include "Key/Core/Buffer.h"
#include "Key/Renderer/Buffer.h"

namespace Key {
	//////////////////////////////////////////////////////////////////////////////////
	// VertexBuffer
	//////////////////////////////////////////////////////////////////////////////////
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(void* data, uint32_t size, VertexBufferUsage usage = VertexBufferUsage::Static);
		OpenGLVertexBuffer(uint32_t size, VertexBufferUsage usage = VertexBufferUsage::Dynamic);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;


		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }

		//3D
		virtual void SetData(void* data, uint32_t size, uint32_t offset = 0);
		virtual uint32_t GetSize() const { return m_Size; }
		virtual RendererID GetRendererID() const { return m_RendererID; }
		//3D---end
	private:
		RendererID m_RendererID = 0;
		uint32_t m_Size;
		VertexBufferUsage m_Usage;
		BufferLayout m_Layout;

		Buffer m_LocalData;
	};


	//////////////////////////////////////////////////////////////////////////////////
	// IndexBuffer
	//////////////////////////////////////////////////////////////////////////////////
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		//3D
		OpenGLIndexBuffer(uint32_t size);
		OpenGLIndexBuffer(void* data, uint32_t size);
		//3D---end
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;


		virtual uint32_t GetCount() const { return m_Size / sizeof(uint32_t); }

		//3d
		virtual uint32_t GetSize() const { return m_Size; }
		virtual RendererID GetRendererID() const { return m_RendererID; }
		virtual void SetData(void* data, uint32_t size, uint32_t offset = 0);
	private:
		RendererID m_RendererID = 0;
		uint32_t m_Size;

		Buffer m_LocalData;
	};
}

