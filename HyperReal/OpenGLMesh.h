#pragma once
#include "core-files/Renderer/Mesh.h"

namespace HyperR {

	struct Vertex {
		glm::vec3 Position;
		//glm::vec3 Normal;
		glm::vec2 TexCoord;
		// Add more (tangent, bitangent, boneIDs, weights) if needed
	};

	class OpenGLMesh : public HyperR::Mesh
	{
	public:
		OpenGLMesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);

		const Ref<VertexArray>& GetVertexArray() const { return m_VertexArray; }
		virtual void Bind() const override;
		virtual void Unbind() const override;
	
	private: 
		void SetupMesh();
	private:

		std::vector<Vertex> m_Vertices;
		std::vector<uint32_t> m_Indices;

		Ref<VertexArray> m_VertexArray;
		Ref<VertexBuffer> m_VertexBuffer;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}

