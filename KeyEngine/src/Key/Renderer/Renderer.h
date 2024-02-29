#pragma once

#include "Key/Core/Base.h"
#include "RenderCommand.h"
#include "RenderCommandQueue.h"
#include "RendererAPI.h"
#include "OrthographicCamera.h"
#include "Shader.h"

namespace Key {

	class Renderer
	{
	public:
		typedef void(*RenderCommandFn)(void*);

		//Commands
		static void Init();
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4 transform = glm::mat4(1.0f));
		static void OnWindowResize(uint32_t width, uint32_t height);
		inline static RendererAPI::RendererAPIType GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};

}

