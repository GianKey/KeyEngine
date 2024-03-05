#pragma once
#include "Key/Renderer/Renderer.h"

namespace Key {

	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};
	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:		return 4;
		case ShaderDataType::Float2:	return 4 * 2;
		case ShaderDataType::Float3:	return 4 * 3;
		case ShaderDataType::Float4:	return 4 * 4;
		case ShaderDataType::Mat3:		return 4 * 3 * 3;
		case ShaderDataType::Mat4:		return 4 * 4 * 4;
		case ShaderDataType::Int:			return 4;
		case ShaderDataType::Int2:		return 4 * 2;
		case ShaderDataType::Int3:		return 4 * 3;
		case ShaderDataType::Int4:		return 4 * 4;
		case ShaderDataType::Bool:		return 1;
		}
		KEY_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;

		BufferElement() = default;
		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Type(type), Name(name), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
			case ShaderDataType::Float:		return 1;
			case ShaderDataType::Float2:	return 2;
			case ShaderDataType::Float3:	return 3;
			case ShaderDataType::Float4:	return 4;
			case ShaderDataType::Mat3:		return 3 * 3;
			case ShaderDataType::Mat4:		return 4 * 4;
			case ShaderDataType::Int:			return 1;
			case ShaderDataType::Int2:		return 2;
			case ShaderDataType::Int3:		return 3;
			case ShaderDataType::Int4:		return 4;
			case ShaderDataType::Bool:		return 1;
			}
			KEY_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	};


	class BufferLayout
	{
	public:

		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements)
		{
			CalculateOffsetAndStride();
		}

		inline uint32_t GetStride() const { return m_Stride; }
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	private:
		void CalculateOffsetAndStride()
		{
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;		//初始化每个element的 offset 并计算总步长
				offset += element.Size;
				m_Stride += element.Size;
			}
		}
	private:
		std::vector<BufferElement> m_Elements;  //	存放每一个顶点属性对应一个 Element
		uint32_t m_Stride = 0;									//步长，代表一个顶点的所有数据的长度
	};



	enum class VertexBufferUsage
	{
		None = 0, Static = 1, Dynamic = 2
	};


	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;
		static VertexBuffer* Create(float* vertices, uint32_t size);
		//3D
		virtual unsigned int GetSize() const = 0;
		virtual RendererID GetRendererID() const = 0;
		virtual void SetData(void* buffer, uint32_t size, uint32_t offset = 0) = 0;
		static Ref<VertexBuffer> Create(void* data, uint32_t size, VertexBufferUsage usage = VertexBufferUsage::Static);
		static Ref<VertexBuffer> Create(uint32_t size, VertexBufferUsage usage = VertexBufferUsage::Dynamic);
		//3D---end
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;

		virtual uint32_t GetCount() const = 0;


		//3D
		virtual void SetData(void* buffer, uint32_t size, uint32_t offset = 0) = 0;
		virtual unsigned int GetSize() const = 0;
		virtual RendererID GetRendererID() const = 0;
		static Ref<IndexBuffer> Create(void* data, uint32_t size = 0);
		//3D---end
	};
}

