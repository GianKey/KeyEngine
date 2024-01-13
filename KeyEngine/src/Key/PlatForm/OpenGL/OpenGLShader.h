#pragma once
#include "Key/Renderer/shader.h"
#include <memory>

namespace Key {
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& VertexSrc, const std::string& FragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		void UpLoadUniformInt(const std::string& name, int value);


		void UpLoadUniformFloat(const std::string& name, float value);
		void UpLoadUniformFloat2(const std::string& name, const glm::vec2& values);
		void UpLoadUniformFloat3(const std::string& name, const glm::vec3& values);
		void UpLoadUniformFloat4(const std::string& name, const glm::vec4& values);

		void UpLoadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UpLoadUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		uint32_t m_RendererID;

	};

}