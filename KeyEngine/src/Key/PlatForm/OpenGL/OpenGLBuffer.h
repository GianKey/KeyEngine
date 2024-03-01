#pragma once
#include "Key/Renderer/Buffer.h"

namespace Key {
	//////////////////////////////////////////////////////////////////////////////////
	// VertexBuffer
	//////////////////////////////////////////////////////////////////////////////////
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(unsigned int size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;


		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }

		//3D
		virtual void SetData(void* buffer, unsigned int size, unsigned int offset = 0);
		virtual unsigned int GetSize() const { return m_Size; }
		virtual RendererID GetRendererID() const { return m_RendererID; }
		//3D---end
	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
		unsigned int m_Size;
	};


	//////////////////////////////////////////////////////////////////////////////////
	// IndexBuffer
	//////////////////////////////////////////////////////////////////////////////////
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		//3D
		OpenGLIndexBuffer(unsigned int size);
		//3D---end
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;


		virtual uint32_t GetCount() const { return m_Size / sizeof(uint32_t); }

		//3d
		virtual unsigned int GetSize() const { return m_Size; }
		virtual RendererID GetRendererID() const { return m_RendererID; }
		virtual void SetData(void* buffer, unsigned int size, unsigned int offset = 0);
	private:
		uint32_t m_RendererID;
		unsigned int m_Size;
	};
}

