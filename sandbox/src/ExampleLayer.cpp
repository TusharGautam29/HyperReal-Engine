#include "ExampleLayer.h"

#include "imgui/imgui.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>

ExampleLayer::ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f)
	{
		m_VertexArray = HyperR::VertexArray::Create();

		float vertices[3 * 7] = {
					-0.5f, -0.5f, 0.0f, 1.0f, 0.8f, 0.5f, 1.0f,
					 0.5f, -0.5f, 0.0f, 0.7f, 1.0f, 0.2f, 1.0f,
					 0.0f,  0.5f, 0.0f, 0.3f, 0.2f, 1.0f, 0.5f
		};

		HyperR::Ref<HyperR::VertexBuffer> vertexBuffer;

		vertexBuffer.reset(HyperR::VertexBuffer::Create(vertices, sizeof(vertices)));

		HyperR::BufferLayout layout = {
			{ HyperR::ShaderDataType::Float3, "a_Position" },
			{ HyperR::ShaderDataType::Float4, "a_Color" }

		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);


		uint32_t indices[3] = { 0, 1, 2 };

		HyperR::Ref<HyperR::IndexBuffer> indexBuffer = HyperR::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA = HyperR::VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		HyperR::Ref<HyperR::VertexBuffer> squareVB;

		squareVB.reset(HyperR::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{ HyperR::ShaderDataType::Float3, "a_Position" },
			{ HyperR::ShaderDataType::Float2, "a_TexCoord" }
			});

		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

		std::shared_ptr<HyperR::IndexBuffer> squareIB = HyperR::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));

		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;		

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";
		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";
		m_Shader = HyperR::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";
		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;

			uniform vec3 u_Color;
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
				color = vec4(u_Color, 1.0);
			}
		)";
		m_FlatColorShader = (HyperR::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc));


		auto m_TextureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = HyperR::Texture2D::Create("assets/textures/Checkerboard.png");
		m_LogoTexture = HyperR::Texture2D::Create("assets/textures/sample.jpeg");
		std::dynamic_pointer_cast<HyperR::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<HyperR::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
}

void ExampleLayer::OnUpdate(HyperR::Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	HyperR::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	HyperR::RenderCommand::Clear();


	HyperR::Renderer::BeginScene(m_CameraController.GetCamera());

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	std::dynamic_pointer_cast<HyperR::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<HyperR::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
			HyperR::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
		}
	}

	auto m_TextureShader = m_ShaderLibrary.Get("Texture");
	m_Texture->Bind();
	HyperR::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	m_LogoTexture->Bind();
	HyperR::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
	// Triangle
	// HyperR::Renderer::Submit(m_Shader, m_VertexArray);

	HyperR::Renderer::EndScene();
}
void ExampleLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}
void ExampleLayer::OnEvent(HyperR::Event& event)
{
	m_CameraController.OnEvent(event);
}
void ExampleLayer::OnAttach()
{
}
void ExampleLayer::OnDetach()
{
}