#include "Kpch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "Key/Core/Log.h"

namespace Key {

	OpenGLContext::OpenGLContext()
	{
	}

	OpenGLContext::~OpenGLContext()
	{
	}

	void OpenGLContext::Init()
	{
		KEY_CORE_INFO("OpenGLContext::Create");

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		KEY_CORE_ASSERT(status, "Failed to initialize Glad!");

		KEY_CORE_INFO("OpenGL Info:");
		KEY_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		KEY_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		KEY_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

#ifdef KEY_ENABLE_ASSERTS
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		KEY_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Key requires at least OpenGL version 4.5!");
#endif
	}

	//void OpenGLContext::SwapBuffers()
	//{
	//	glfwSwapBuffers(m_WindowHandle);
	//}

}