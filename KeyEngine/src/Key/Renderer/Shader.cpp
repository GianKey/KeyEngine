#include "Kpch.h"
#include "Shader.h"
#include "Key/Renderer/Renderer.h"
#include "Key/PlatForm/OpenGL/OpenGLShader.h"
#include "Key/Renderer/RendererAPI.h"
#include <glad/glad.h>

namespace Key {

	std::vector<Ref<Shader>> Shader::s_AllShaders;

	Ref<Shader>  Shader::Create(const std::string& filepath)
	{
		Ref<Shader> result = nullptr;
		switch (RendererAPI::Current())
		{
			case RendererAPIType::None:    KEY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPIType::OpenGL:  result = CreateRef<OpenGLShader>(filepath);
		}

		KEY_CORE_ASSERT(false, "Unknown RendererAPI!");
		s_AllShaders.push_back(result);
		return result;
	}

	ShaderLibrary::ShaderLibrary()
	{
	}

	ShaderLibrary::~ShaderLibrary()
	{
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		KEY_CORE_ASSERT(!Exists(name), "Shader already exists!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	void ShaderLibrary::Load(const std::string& path)
	{
		auto shader = Ref<Shader>(Shader::Create(path));
		auto& name = shader->GetName();
		KEY_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end());
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Load(const std::string& name, const std::string& path)
	{
		KEY_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end());
		m_Shaders[name] = Ref<Shader>(Shader::Create(path));
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		KEY_CORE_ASSERT(Exists(name), "Shader not found!");

		return m_Shaders[name];
	}
	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}
}
