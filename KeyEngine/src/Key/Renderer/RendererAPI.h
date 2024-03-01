#pragma once
#include <glm/glm.hpp>
//#include "VertexArray.h"
namespace Key {
	using RendererID = uint32_t;

	enum class RendererAPIType
	{
		None = 0, OpenGL = 1
	};
	struct RenderAPICapabilities
	{
		std::string Vendor;
		std::string Renderer;
		std::string Version;

		int MaxSamples;
		float MaxAnisotropy;
	};

	class RendererAPI
	{
	public:
		
	public:
		/*virtual void Init() = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;*/
		static void Init();
		static void Shutdown();

		static void Clear(float r, float g, float b, float a);
		static void SetClearColor(float r, float g, float b, float a);

		static void DrawIndexed(unsigned int count, bool depthTest = true);

		static RenderAPICapabilities& GetCapabilities()
		{
			static RenderAPICapabilities capabilities;
			return capabilities;
		}
		static RendererAPIType Current() { return s_CurrentRendererAPI; }

		//Key
		inline static RendererAPIType GetAPI() { return s_CurrentRendererAPI; }

	private:
		static RendererAPIType s_CurrentRendererAPI;
	private:
		static void LoadRequiredAssets();
	};

}