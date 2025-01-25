#include "hrpch.h"

#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace HyperR {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}