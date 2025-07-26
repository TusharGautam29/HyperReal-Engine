#include "hrpch.h"
#include "OpenGLMesh.h"

namespace HyperR {

	OpenGLMesh::OpenGLMesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
		: m_Vertices(vertices), m_Indices(indices)
	{
		SetupMesh();
	}

	void OpenGLMesh::SetupMesh()
	{
		m_VertexArray = VertexArray::Create();

		m_VertexBuffer = CreateRef<VertexBuffer>((float*)m_Vertices.data(), m_Vertices.size() * sizeof(Vertex));

		m_VertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			//{ ShaderDataType::Float3, "a_Normal" },
			{ ShaderDataType::Float2, "a_TexCoord" }
			});
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		m_IndexBuffer = IndexBuffer::Create(m_Indices.data(), m_Indices.size());
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);
	}

	void OpenGLMesh::Bind() const
	{
		m_VertexArray->Bind();
	}

	void OpenGLMesh::Unbind() const
	{
		m_VertexArray->Unbind();
	}

}

