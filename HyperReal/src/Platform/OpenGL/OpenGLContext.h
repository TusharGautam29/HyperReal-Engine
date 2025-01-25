#pragma once
#include "core-files/Renderer/GraphicsContext.h"

struct GLFWwindow;
namespace HyperR {
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}