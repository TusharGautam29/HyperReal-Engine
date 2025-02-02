#pragma once
#include <HyperReal.h>
class Sandbox2D : public HyperR::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	void OnUpdate(HyperR::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(HyperR::Event& e) override;
private:
	HyperR::OrthographicCameraController m_CameraController;

	HyperR::Ref<HyperR::Texture2D> m_CheckerboardTexture;

	// Temp
	HyperR::Ref<HyperR::VertexArray> m_SquareVA;
	HyperR::Ref<HyperR::Shader> m_FlatColorShader;
	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};