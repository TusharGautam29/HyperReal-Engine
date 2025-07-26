#include "Mesh.h"

namespace HyperR {
	Ref<Mesh> Mesh::Create(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    HR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLMesh>(vertices,indices);
		}
		HR_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}