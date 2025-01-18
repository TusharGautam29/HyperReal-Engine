#include <HyperReal.h>
#include "imgui/imgui.h"



class ExampleLayer : public HyperR::Layer
{
public:
	ExampleLayer()
		: Layer("Example"),m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(HyperR::VertexArray::Create());

		float vertices[3 * 7] = {
					-0.5f, -0.5f, 0.0f, 1.0f, 0.8f, 0.5f, 1.0f,
					 0.5f, -0.5f, 0.0f, 0.7f, 1.0f, 0.2f, 1.0f,
					 0.0f,  0.5f, 0.0f, 0.3f, 0.2f, 1.0f, 0.5f
		};

		std::shared_ptr<HyperR::VertexBuffer> vertexBuffer;

		vertexBuffer.reset(HyperR::VertexBuffer::Create(vertices, sizeof(vertices)));

		HyperR::BufferLayout layout = {
			{ HyperR::ShaderDataType::Float3, "a_Position" },
			{ HyperR::ShaderDataType::Float4, "a_Color" }

		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);


		uint32_t indices[3] = { 0, 1, 2 };

		std::shared_ptr<HyperR::IndexBuffer> indexBuffer;

		indexBuffer.reset(HyperR::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(HyperR::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};
		std::shared_ptr<HyperR::VertexBuffer> squareVB;

		squareVB.reset(HyperR::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{ HyperR::ShaderDataType::Float3, "a_Position" }
			});

		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

		std::shared_ptr<HyperR::IndexBuffer> squareIB;

		squareIB.reset(HyperR::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 0) in vec4 a_Color;		

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
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
		m_Shader.reset(new HyperR::Shader(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";
		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";
		m_BlueShader.reset(new HyperR::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
	}
	
	void OnUpdate(HyperR::Timestep ts) override
	{

		if (HyperR::Input::IsKeyPressed(HR_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;

		else if (HyperR::Input::IsKeyPressed(HR_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		
		if (HyperR::Input::IsKeyPressed(HR_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		
		else if (HyperR::Input::IsKeyPressed(HR_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		
		if (HyperR::Input::IsKeyPressed(HR_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		
		if (HyperR::Input::IsKeyPressed(HR_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		HyperR::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		HyperR::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		HyperR::Renderer::BeginScene(m_Camera);

		HyperR::Renderer::Submit(m_BlueShader, m_SquareVA);

		HyperR::Renderer::Submit(m_Shader, m_VertexArray);

		HyperR::Renderer::EndScene();
	}
	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}
	void OnEvent(HyperR::Event& event) override
	{
	}
	private:
		float m_CameraMoveSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
		glm::vec3 m_CameraPosition;
		float m_CameraRotation = 0.0f;
		std::shared_ptr<HyperR::Shader> m_Shader;
		std::shared_ptr<HyperR::VertexArray> m_VertexArray;
		std::shared_ptr<HyperR::Shader> m_BlueShader;
		std::shared_ptr<HyperR::VertexArray> m_SquareVA;
		HyperR::OrthographicCamera m_Camera;
	private:
};

class sandbox : public HyperR::Application
{
public:
	sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~sandbox()
	{
	}
};
HyperR::Application* HyperR::CreateApplication()
{
	return new sandbox();
}