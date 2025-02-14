#include "Kpch.h"
#include "OpenGLUniformBuffer.h"

#include <glad/glad.h>

#include "Key/Renderer/Renderer.h"

namespace Key {

	OpenGLUniformBuffer::OpenGLUniformBuffer(uint32_t size, uint32_t binding)
		: m_Size(size), m_Binding(binding)
	{
		m_LocalStorage = new uint8_t[size];

		Ref<OpenGLUniformBuffer> instance = this;
		Renderer::Submit([instance, size, binding]() mutable
		{
			glCreateBuffers(1, &instance->m_RendererID);
			glNamedBufferData(instance->m_RendererID, size, nullptr, GL_DYNAMIC_DRAW);
			glBindBufferBase(GL_UNIFORM_BUFFER, binding, instance->m_RendererID);
		});
	}

	OpenGLUniformBuffer::~OpenGLUniformBuffer()
	{
		delete[] m_LocalStorage;

		RendererID rendererID = m_RendererID;
		Renderer::Submit([rendererID]()
		{
			glDeleteBuffers(1, &rendererID);
		});
	}

	void OpenGLUniformBuffer::SetData(const void* data, uint32_t size, uint32_t offset)
	{
		// TODO: local storage should be potentially replaced with render thread storage
		memcpy(m_LocalStorage, data, size);
		Ref<OpenGLUniformBuffer> instance = this;
		Renderer::Submit([instance, size, offset]() mutable
		{
			glNamedBufferSubData(instance->m_RendererID, offset, size, instance->m_LocalStorage);
			instance->RT_SetData(instance->m_LocalStorage, size, offset);
		});
	}

	void OpenGLUniformBuffer::RT_SetData(const void* data, uint32_t size, uint32_t offset)
	{
		glNamedBufferSubData(m_RendererID, offset, size, m_LocalStorage);
	}


}
