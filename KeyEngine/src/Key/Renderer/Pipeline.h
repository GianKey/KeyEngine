#pragma once

#include "Key/Core/Ref.h"

#include "Key/Renderer/VertexBuffer.h"
#include "Key/Renderer/Shader.h"

namespace Key {

	struct PipelineSpecification
	{
		Ref<Key::Shader> Shader;
		VertexBufferLayout Layout;
	};

	class Pipeline : public RefCounted
	{
	public:
		virtual ~Pipeline() = default;

		virtual PipelineSpecification& GetSpecification() = 0;
		virtual const PipelineSpecification& GetSpecification() const = 0;

		virtual void Invalidate() = 0;

		// TEMP: remove this when render command buffers are a thing
		virtual void Bind() = 0;

		static Ref<Pipeline> Create(const PipelineSpecification& spec);
	};

}