#include "hrpch.h"	

#include "VertexArray.h"

#include "Renderer.h"
#include "core-files/Platform/OpenGL/OpenGLVertexArray.h"

namespace HyperR {
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:    HR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::OpenGL:  return new OpenGLVertexArray();
		}
		HR_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}