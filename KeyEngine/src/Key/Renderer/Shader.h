#pragma once
#include <string>
namespace Key {
	class Shader
	{
	public:
		Shader(const std::string& VertexSrc, const std::string& FragmentSrc);
		~Shader();

		void Bind() const;				//��Shader �� Program
		void UnBind() const;			//���Shader
	private:
		uint32_t m_RendererID;		//��Ⱦ����ID
	};
}

