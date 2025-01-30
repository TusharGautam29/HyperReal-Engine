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
	m_CameraController.OnUpdate(ts);

	HyperR::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	HyperR::RenderCommand::Clear();


	HyperR::Renderer2D::BeginScene(m_CameraController.GetCamera());

	HyperR::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	HyperR::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	HyperR::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	HyperR::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);
	HyperR::Renderer2D::EndScene();

	/*std::dynamic_pointer_cast<HyperR::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<HyperR::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);
	HyperR::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));*/
}
void Sandbox2D::OnImGuiRender() {
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Flat Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}
void Sandbox2D::OnEvent(HyperR::Event& e) {
	m_CameraController.OnEvent(e);
}
