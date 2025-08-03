#include "Sandbox3D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "core-files/Renderer/Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "core-files/Renderer/Vertex.h"
#include "core-files/Renderer/Renderer2D.h"



Sandbox3D::Sandbox3D()
	: Layer("Sandbox3D"), m_PerspectiveCameraController(45.0f, 1280.0f / 720.0f, 0.1f, 100.0f)
{
}

void Sandbox3D::OnAttach() {
	HR_PROFILE_FUNCTION();

	std::vector<HyperR::Vertex> quadVertices = {
	{{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f}}, // Bottom-left
	{{ 0.5f, -0.5f, 0.0f}, {1.0f, 0.0f}}, // Bottom-right
	{{ 0.5f,  0.5f, 0.0f}, {1.0f, 1.0f}}, // Top-right
	{{-0.5f,  0.5f, 0.0f}, {0.0f, 1.0f}}, // Top-left
	};

	std::vector<uint32_t> quadIndices = {
		0, 1, 2,
		2, 3, 0
	};

	m_Shader = HyperR::Shader::Create("assets/shaders/FlatColor.glsl");
	m_CubeMesh = HyperR::Mesh::Create(quadVertices, quadIndices, m_Shader);

}

void Sandbox3D::OnDetach() {
	HR_PROFILE_FUNCTION();

}
void Sandbox3D::OnUpdate(HyperR::Timestep ts) {
	HR_PROFILE_SCOPE("Sandbox3D::OnUpdate");
	m_PerspectiveCameraController.OnUpdate(ts);

	{
		HR_PROFILE_SCOPE("Renderer Prep");
		HyperR::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.5f, 1.0f });

		HyperR::RenderCommand::Clear();
	}
	{
		HR_PROFILE_SCOPE("Renderer Draw");
		HyperR::Renderer3D::BeginScene(m_PerspectiveCameraController.GetCamera());
		HyperR::Renderer3D::DrawCube({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f });
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
