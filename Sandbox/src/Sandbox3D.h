#pragma once
#include <HyperReal.h>
class Sandbox3D : public HyperR::Layer
{
public:
	Sandbox3D();
	virtual ~Sandbox3D() = default;
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	void OnUpdate(HyperR::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(HyperR::Event& e) override;
private:
	HyperR::PerspectiveCameraController m_PerspectiveCameraController;

	HyperR::Ref<HyperR::Texture2D> m_CheckerboardTexture;

private:
	HyperR::Ref<HyperR::Shader> m_Shader;
	HyperR::Ref<HyperR::Mesh> m_CubeMesh;
	// Temp
	HyperR::Ref<HyperR::VertexArray> m_SquareVA;
	HyperR::Ref<HyperR::Shader> m_FlatColorShader;
	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};