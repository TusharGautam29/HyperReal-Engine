#include "Sandbox3D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "core-files/Renderer/Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "core-files/Renderer/Vertex.h"



Sandbox3D::Sandbox3D()
	: Layer("Sandbox3D"), m_PerspectiveCameraController(45.0f, 1280.0f / 720.0f, 0.1f, 100.0f)
{
}

void Sandbox3D::OnAttach() {
	HR_PROFILE_FUNCTION();

	std::vector<HyperR::Vertex> cubeVertices = {
		{{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},
		{{ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},
		{{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f}},
		{{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f}},
		{{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}},
		{{ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}},
		{{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f}},
		{{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f}},
	};

	std::vector<uint32_t> cubeIndices = {
		0, 1, 2, 2, 3, 0,
		4, 5, 6, 6, 7, 4,
		4, 5, 1, 1, 0, 4,
		6, 7, 3, 3, 2, 6,
		4, 7, 3, 3, 0, 4,
		5, 6, 2, 2, 1, 5
	};

	m_Shader = HyperR::Shader::Create("assets/shaders/FlatColor.glsl");
	m_CubeMesh = HyperR::Mesh::Create(cubeVertices, cubeIndices, m_Shader);
}

void Sandbox3D::OnDetach() {
	HR_PROFILE_FUNCTION();

}
void Sandbox3D::OnUpdate(HyperR::Timestep ts) {
	HR_PROFILE_SCOPE("Sandbox3D::OnUpdate");
	m_PerspectiveCameraController.OnUpdate(ts);

	{
		HR_PROFILE_SCOPE("Renderer Prep");
		HyperR::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		HyperR::RenderCommand::Clear();
	}
	{
		HR_PROFILE_SCOPE("Renderer Draw");
		HyperR::Renderer3D::BeginScene(m_PerspectiveCameraController.GetCamera());

		glm::mat4 transform = glm::mat4(1.0f);
		HyperR::Renderer3D::Submit(m_CubeMesh, transform);

		HyperR::Renderer3D::EndScene();
	}
}

void Sandbox3D::OnImGuiRender() {
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Flat Color", glm::value_ptr(m_SquareColor));

	ImGui::End();
}
void Sandbox3D::OnEvent(HyperR::Event& e) {
	m_PerspectiveCameraController.OnEvent(e);
}
