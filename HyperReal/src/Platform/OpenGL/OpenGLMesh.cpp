#include "hrpch.h"
#include "OpenGLMesh.h"

namespace HyperR {

	OpenGLMesh::OpenGLMesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const Ref<Shader>& shader)
		: m_Vertices(vertices), m_Indices(indices), m_Shader(shader)
	{
		SetupMesh();
	}

	void OpenGLMesh::SetupMesh()
	{
		m_VertexArray = VertexArray::Create();

		m_VertexBuffer = VertexBuffer::Create((float*)m_Vertices.data(), m_Vertices.size() * sizeof(Vertex));


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
	void OpenGLMesh::Draw() const {
		m_VertexArray->Bind();
		RenderCommand::DrawIndexed(m_VertexArray);
	}
	const Ref<Shader>& OpenGLMesh::GetShader() const {
		return m_Shader;
	}
}

