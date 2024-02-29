#include "Kpch.h"
#include "RendererAPI.h"

namespace Key {
	RendererAPI::RendererAPIType RendererAPI::s_CurrentRendererAPI = RendererAPI::RendererAPIType::OpenGL;
}