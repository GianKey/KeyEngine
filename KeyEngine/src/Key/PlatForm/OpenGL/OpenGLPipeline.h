#pragma once

#include "Key/Renderer/Pipeline.h"

namespace Key {

	class OpenGLPipeline : public Pipeline
	{
	public:
		OpenGLPipeline(const PipelineSpecification& spec);
		virtual ~OpenGLPipeline();

		virtual PipelineSpecification& GetSpecification() { return m_Specification; }
		virtual const PipelineSpecification& GetSpecification() const { return m_Specification; }

		virtual void Invalidate() override;

		virtual void Bind() override;
	private:
		PipelineSpecification m_Specification;
		uint32_t m_VertexArrayRendererID = 0;
	};

}