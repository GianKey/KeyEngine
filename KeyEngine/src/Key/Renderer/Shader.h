#pragma once
#include <string>
#include <glm/glm.hpp>
namespace Key {
	class Shader
	{
	public:
		Shader(const std::string& VertexSrc, const std::string& FragmentSrc);
		~Shader();

		void Bind() const;				//绑定Shader 到 Program
		void UnBind() const;			//解绑Shader

		void UpLoadUniformMat4(const std::string& name,const glm::mat4& matrix);
	private:
		uint32_t m_RendererID;		//渲染程序ID
	};
}

