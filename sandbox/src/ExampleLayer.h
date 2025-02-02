#pragma once
#include "HyperReal.h"
class ExampleLayer : public HyperR::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	void OnUpdate(HyperR::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(HyperR::Event& e) override;
private:
	HyperR::OrthographicCameraController m_CameraController;

	HyperR::ShaderLibrary m_ShaderLibrary;
	HyperR::Ref<HyperR::Shader> m_Shader;
	HyperR::Ref<HyperR::VertexArray> m_VertexArray;
	HyperR::Ref<HyperR::Shader> m_FlatColorShader;

	HyperR::Ref<HyperR::VertexArray> m_SquareVA;
	HyperR::Ref<HyperR::Texture2D> m_Texture;
	HyperR::Ref<HyperR::Texture2D> m_LogoTexture;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};