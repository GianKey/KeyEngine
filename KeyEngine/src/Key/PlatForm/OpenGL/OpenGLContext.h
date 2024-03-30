#pragma once

#include "Key/Renderer/RendererContext.h"

struct GLFWwindow;

namespace Key {

	class OpenGLContext : public RendererContext
	{
	public:
		OpenGLContext();
		virtual ~OpenGLContext();

		virtual void Init() override;
	private:
		GLFWwindow* m_WindowHandle;
	};

}
