#pragma once
#include "core-files/Renderer/Mesh.h"
#include "core-files/Renderer/Vertex.h"

namespace HyperR {

	

	class OpenGLMesh : public HyperR::Mesh
	{
	public:
		OpenGLMesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const Ref<Shader>& shader);

		const Ref<VertexArray>& GetVertexArray() const { return m_VertexArray; }
		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void Draw() const override;
		virtual const Ref<Shader>& GetShader() const override;
	
	private: 
		void SetupMesh();
	private:

		std::vector<Vertex> m_Vertices;
		std::vector<uint32_t> m_Indices;

		Ref<VertexArray> m_VertexArray;
		Ref<VertexBuffer> m_VertexBuffer;
		Ref<IndexBuffer> m_IndexBuffer;
		Ref<Shader> m_Shader;
	};
}

