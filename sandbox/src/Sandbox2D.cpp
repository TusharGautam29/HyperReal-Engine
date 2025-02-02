#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"



Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f) 
{
}

void Sandbox2D::OnAttach(){
	
	m_CheckerboardTexture = HyperR::Texture2D::Create("assets/textures/Checkerboard.png");

}
void Sandbox2D::OnDetach() {

}
void Sandbox2D::OnUpdate(HyperR::Timestep ts) {

	HR_PROFILE_SCOPE("Sandbox2D::OnUpdate");
	// Update
	{
		HR_PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}

	{
		HR_PROFILE_SCOPE("Renderer Prep");
		HyperR::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		HyperR::RenderCommand::Clear();
	}
	{
		HR_PROFILE_SCOPE("Renderer Draw");
		HyperR::Renderer2D::BeginScene(m_CameraController.GetCamera());
		HyperR::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, m_SquareColor);
		HyperR::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		HyperR::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);
		HyperR::Renderer2D::EndScene();
	}
}
void Sandbox2D::OnImGuiRender() {
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Flat Color", glm::value_ptr(m_SquareColor));

	ImGui::End();
}
void Sandbox2D::OnEvent(HyperR::Event& e) {
	m_CameraController.OnEvent(e);
}
