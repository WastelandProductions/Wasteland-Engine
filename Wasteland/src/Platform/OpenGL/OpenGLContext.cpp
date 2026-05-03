#include "wlpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Wasteland {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		WL_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		WL_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		WL_CORE_ASSERT(status, "Failed to initialize Glad!");

		WL_CORE_INFO("OpenGL Info:");
		WL_CORE_INFO(" Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		WL_CORE_INFO(" Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		WL_CORE_INFO(" Version: {0}", (const char*)glGetString(GL_VERSION));

#ifdef WL_ENABLE_ASSERTS
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		WL_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Wasteland requires at least OpenGL version 4.5!");
#endif
	}

	void OpenGLContext::SwapBuffers()
	{
		WL_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}

}