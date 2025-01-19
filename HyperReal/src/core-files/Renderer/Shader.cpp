#include "hrpch.h"
#include "Shader.h"
#include "Renderer.h"
#include "core-files/Platform/OpenGL/OpenGLShader.h"

namespace HyperR {
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    HR_CORE_ASSERT(false, "RenderererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return new OpenGLShader(vertexSrc, fragmentSrc);
		}
		HR_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;

	}
}
