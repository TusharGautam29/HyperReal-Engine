#include "hrpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>
namespace HyperR {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		HR_CORE_ASSERT(windowHandle, "Window handle is null!")
	}
	void OpenGLContext::Init()
	{
		HR_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HR_CORE_ASSERT(status, "Failed to initialize Glad!");
		
		HR_CORE_INFO("OpenGL Info:");
		HR_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		HR_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		HR_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));


	}
	void OpenGLContext::SwapBuffers()
	{

		HR_PROFILE_FUNCTION();
		glfwSwapBuffers(m_WindowHandle);
	}
}