#pragma once
#include "Key/Renderer/shader.h"
#include <memory>
// TODO: REMOVE!
typedef unsigned int GLenum;
namespace Key {
	class OpenGLShader : public Shader
	{
	public:
		//OpenGLShader(const std::string& VertexSrc, const std::string& FragmentSrc);
		OpenGLShader(const std::string& filepath);

		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

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