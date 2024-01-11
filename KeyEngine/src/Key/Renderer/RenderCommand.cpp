#include "Kpch.h"
#include "RenderCommand.h"

#include "Key/PlatForm/OpenGL/OpenGLRendererAPI.h"

namespace Key {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}