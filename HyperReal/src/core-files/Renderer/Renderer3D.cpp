#include "hrpch.h"
#include "Renderer3D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Platform/OpenGL/OpenGLShader.h"

namespace HyperR {

	struct CubeVertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoord;
		glm::vec4 Color;
	};

	struct Renderer3DStorage
	{
		const uint32_t MaxCubes = 5000;
		const uint32_t MaxVertices = MaxCubes * 24; // 24 vertices per cube (4 per face * 6 faces)
		const uint32_t MaxIndices = MaxCubes * 36;  // 36 indices per cube (6 per face * 6 faces)

		Ref<VertexArray> CubeVertexArray;
		Ref<VertexBuffer> CubeVertexBuffer;
		Ref<Texture2D> WhiteTexture;
		Ref<Shader> PerspectiveShader;

		uint32_t CubeIndexCount = 0;
		CubeVertex* CubeVertexBufferBase = nullptr;
		CubeVertex* CubeVertexBufferPtr = nullptr;

		// Cube face normals
		static constexpr glm::vec3 FaceNormals[6] = {
			{ 0.0f,  0.0f,  1.0f}, // Front
			{ 0.0f,  0.0f, -1.0f}, // Back
			{-1.0f,  0.0f,  0.0f}, // Left
			{ 1.0f,  0.0f,  0.0f}, // Right
			{ 0.0f,  1.0f,  0.0f}, // Top
			{ 0.0f, -1.0f,  0.0f}  // Bottom
		};
	};

	static Renderer3DStorage s_Data;

	void Renderer3D::Init()
	{
		HR_PROFILE_FUNCTION();

		s_Data.CubeVertexArray = VertexArray::Create();
		s_Data.CubeVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(CubeVertex));

		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float3, "a_Normal" },
			{ ShaderDataType::Float2, "a_TexCoord" },
			{ ShaderDataType::Float4, "a_Color" }
		};
		s_Data.CubeVertexBuffer->SetLayout(layout);
		s_Data.CubeVertexArray->AddVertexBuffer(s_Data.CubeVertexBuffer);

		s_Data.CubeVertexBufferBase = new CubeVertex[s_Data.MaxVertices];

		uint32_t* cubeIndices = new uint32_t[s_Data.MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.MaxIndices; i += 36)
		{
			// Generate indices for each face of the cube
			for (uint32_t face = 0; face < 6; face++)
			{
				uint32_t faceOffset = i + face * 6;
				uint32_t vertexOffset = offset + face * 4;

				// Two triangles per face
				cubeIndices[faceOffset + 0] = vertexOffset + 0;
				cubeIndices[faceOffset + 1] = vertexOffset + 1;
				cubeIndices[faceOffset + 2] = vertexOffset + 2;

				cubeIndices[faceOffset + 3] = vertexOffset + 2;
				cubeIndices[faceOffset + 4] = vertexOffset + 3;
				cubeIndices[faceOffset + 5] = vertexOffset + 0;
			}
			offset += 24; // 24 vertices per cube
		}

		Ref<IndexBuffer> cubeIB = IndexBuffer::Create(cubeIndices, s_Data.MaxIndices);
		s_Data.CubeVertexArray->SetIndexBuffer(cubeIB);
		delete[] cubeIndices;

		// Create white texture
		s_Data.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		// Load 3D shader
		s_Data.PerspectiveShader = Shader::Create("assets/shaders/FlatColor.glsl");
		s_Data.PerspectiveShader->Bind();
		s_Data.PerspectiveShader->SetInt("u_Texture", 0);
	}

	void Renderer3D::BeginScene(const PerspectiveCamera& camera)
	{
		HR_PROFILE_FUNCTION();

		s_Data.PerspectiveShader->Bind();
		s_Data.PerspectiveShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		//s_Data.PerspectiveShader->SetFloat3("u_CameraPosition", camera.GetPosition());

		s_Data.CubeIndexCount = 0;
		s_Data.CubeVertexBufferPtr = s_Data.CubeVertexBufferBase;

		// Clear depth buffer
		RenderCommand::Clear();
	}

	void Renderer3D::Shutdown()
	{
		HR_PROFILE_FUNCTION();
		delete[] s_Data.CubeVertexBufferBase;
	}

	void Renderer3D::EndScene()
	{
		HR_PROFILE_FUNCTION();
		uint32_t dataSize = (uint8_t*)s_Data.CubeVertexBufferPtr - (uint8_t*)s_Data.CubeVertexBufferBase;
		s_Data.CubeVertexBuffer->SetData(s_Data.CubeVertexBufferBase, dataSize);

		Flush();
	}

	void Renderer3D::Flush()
	{
		if (s_Data.CubeIndexCount)
			RenderCommand::DrawIndexed(s_Data.CubeVertexArray, s_Data.CubeIndexCount);
	}

	void Renderer3D::DrawCube(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color)
	{
		HR_PROFILE_FUNCTION();

		// Check if we need to flush
		if (s_Data.CubeIndexCount >= s_Data.MaxIndices)
		{
			EndScene();
			s_Data.CubeIndexCount = 0;
			s_Data.CubeVertexBufferPtr = s_Data.CubeVertexBufferBase;
		}

		// Generate cube vertices (24 vertices total - 4 per face)
		glm::vec3 halfSize = size * 0.5f;

		// Face vertices in local space
		glm::vec3 faceVertices[6][4] = {
			// Front face (Z+)
			{{ -halfSize.x, -halfSize.y,  halfSize.z }, {  halfSize.x, -halfSize.y,  halfSize.z },
			 {  halfSize.x,  halfSize.y,  halfSize.z }, { -halfSize.x,  halfSize.y,  halfSize.z }},
			 // Back face (Z-)
			 {{  halfSize.x, -halfSize.y, -halfSize.z }, { -halfSize.x, -halfSize.y, -halfSize.z },
			  { -halfSize.x,  halfSize.y, -halfSize.z }, {  halfSize.x,  halfSize.y, -halfSize.z }},
			  // Left face (X-)
			  {{ -halfSize.x, -halfSize.y, -halfSize.z }, { -halfSize.x, -halfSize.y,  halfSize.z },
			   { -halfSize.x,  halfSize.y,  halfSize.z }, { -halfSize.x,  halfSize.y, -halfSize.z }},
			   // Right face (X+)
			   {{  halfSize.x, -halfSize.y,  halfSize.z }, {  halfSize.x, -halfSize.y, -halfSize.z },
				{  halfSize.x,  halfSize.y, -halfSize.z }, {  halfSize.x,  halfSize.y,  halfSize.z }},
				// Top face (Y+)
				{{ -halfSize.x,  halfSize.y,  halfSize.z }, {  halfSize.x,  halfSize.y,  halfSize.z },
				 {  halfSize.x,  halfSize.y, -halfSize.z }, { -halfSize.x,  halfSize.y, -halfSize.z }},
				 // Bottom face (Y-)
				 {{ -halfSize.x, -halfSize.y, -halfSize.z }, {  halfSize.x, -halfSize.y, -halfSize.z },
				  {  halfSize.x, -halfSize.y,  halfSize.z }, { -halfSize.x, -halfSize.y,  halfSize.z }}
		};

		// Texture coordinates for each vertex of a face
		glm::vec2 texCoords[4] = {
			{ 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f }
		};

		// Generate vertices for all 6 faces
		for (int face = 0; face < 6; face++)
		{
			for (int vertex = 0; vertex < 4; vertex++)
			{
				s_Data.CubeVertexBufferPtr->Position = position + faceVertices[face][vertex];
				s_Data.CubeVertexBufferPtr->Normal = s_Data.FaceNormals[face];
				s_Data.CubeVertexBufferPtr->TexCoord = texCoords[vertex];
				s_Data.CubeVertexBufferPtr->Color = color;
				s_Data.CubeVertexBufferPtr++;
			}
		}

		s_Data.CubeIndexCount += 36;
	}

	void Renderer3D::DrawCube(const glm::vec3& position, const glm::vec3& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		HR_PROFILE_FUNCTION();

		// Bind texture
		texture->Bind();
		s_Data.PerspectiveShader->SetFloat4("u_Color", tintColor);
		s_Data.PerspectiveShader->SetFloat("u_TilingFactor", tilingFactor);

		DrawCube(position, size, tintColor);
	}

	void Renderer3D::DrawRotatedCube(const glm::vec3& position, const glm::vec3& size, const glm::vec3& rotation, const glm::vec4& color)
	{
		HR_PROFILE_FUNCTION();

		// For rotated cubes, we need to transform the vertices
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), { 1.0f, 0.0f, 0.0f }) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), { 0.0f, 1.0f, 0.0f }) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), { 0.0f, 0.0f, 1.0f });

		DrawTransformedCube(transform, size, color);
	}

	void Renderer3D::DrawRotatedCube(const glm::vec3& position, const glm::vec3& size, const glm::vec3& rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		HR_PROFILE_FUNCTION();

		texture->Bind();
		s_Data.PerspectiveShader->SetFloat4("u_Color", tintColor);
		s_Data.PerspectiveShader->SetFloat("u_TilingFactor", tilingFactor);

		DrawRotatedCube(position, size, rotation, tintColor);
	}

	void Renderer3D::DrawTransformedCube(const glm::mat4& transform, const glm::vec3& size, const glm::vec4& color)
	{
		HR_PROFILE_FUNCTION();

		// Check if we need to flush
		if (s_Data.CubeIndexCount >= s_Data.MaxIndices)
		{
			EndScene();
			s_Data.CubeIndexCount = 0;
			s_Data.CubeVertexBufferPtr = s_Data.CubeVertexBufferBase;
		}

		glm::vec3 halfSize = size * 0.5f;
		glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(transform)));

		// Face vertices in local space
		glm::vec3 faceVertices[6][4] = {
			// Front face (Z+)
			{{ -halfSize.x, -halfSize.y,  halfSize.z }, {  halfSize.x, -halfSize.y,  halfSize.z },
			 {  halfSize.x,  halfSize.y,  halfSize.z }, { -halfSize.x,  halfSize.y,  halfSize.z }},
			 // Back face (Z-)
			 {{  halfSize.x, -halfSize.y, -halfSize.z }, { -halfSize.x, -halfSize.y, -halfSize.z },
			  { -halfSize.x,  halfSize.y, -halfSize.z }, {  halfSize.x,  halfSize.y, -halfSize.z }},
			  // Left face (X-)
			  {{ -halfSize.x, -halfSize.y, -halfSize.z }, { -halfSize.x, -halfSize.y,  halfSize.z },
			   { -halfSize.x,  halfSize.y,  halfSize.z }, { -halfSize.x,  halfSize.y, -halfSize.z }},
			   // Right face (X+)
			   {{  halfSize.x, -halfSize.y,  halfSize.z }, {  halfSize.x, -halfSize.y, -halfSize.z },
				{  halfSize.x,  halfSize.y, -halfSize.z }, {  halfSize.x,  halfSize.y,  halfSize.z }},
				// Top face (Y+)
				{{ -halfSize.x,  halfSize.y,  halfSize.z }, {  halfSize.x,  halfSize.y,  halfSize.z },
				 {  halfSize.x,  halfSize.y, -halfSize.z }, { -halfSize.x,  halfSize.y, -halfSize.z }},
				 // Bottom face (Y-)
				 {{ -halfSize.x, -halfSize.y, -halfSize.z }, {  halfSize.x, -halfSize.y, -halfSize.z },
				  {  halfSize.x, -halfSize.y,  halfSize.z }, { -halfSize.x, -halfSize.y,  halfSize.z }}
		};

		glm::vec2 texCoords[4] = {
			{ 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f }
		};

		// Generate vertices for all 6 faces
		for (int face = 0; face < 6; face++)
		{
			glm::vec3 transformedNormal = glm::normalize(normalMatrix * s_Data.FaceNormals[face]);

			for (int vertex = 0; vertex < 4; vertex++)
			{
				glm::vec4 worldPos = transform * glm::vec4(faceVertices[face][vertex], 1.0f);
				s_Data.CubeVertexBufferPtr->Position = glm::vec3(worldPos);
				s_Data.CubeVertexBufferPtr->Normal = transformedNormal;
				s_Data.CubeVertexBufferPtr->TexCoord = texCoords[vertex];
				s_Data.CubeVertexBufferPtr->Color = color;
				s_Data.CubeVertexBufferPtr++;
			}
		}

		s_Data.CubeIndexCount += 36;
	}
}