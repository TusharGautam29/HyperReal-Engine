#include "hrpch.h"

#include "RenderCommand.h"
#include "core-files/Platform/OpenGL/OpenGLRendererAPI.h"

namespace HyperR {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}