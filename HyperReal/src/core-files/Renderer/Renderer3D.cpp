#include "hrpch.h"
#include "Renderer3D.h"
#include "RenderCommand.h"
#include "Shader.h"

namespace HyperR {

	Renderer3D::SceneData* Renderer3D::m_SceneData = new Renderer3D::SceneData;

	void Renderer3D::Init()
	{
		// No-op for now, could init global shaders later
	}

	void Renderer3D::Shutdown()
	{
		delete m_SceneData;
		m_SceneData = nullptr;
	}

	void Renderer3D::BeginScene(const PerspectiveCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer3D::EndScene()
	{
		// No-op for now
	}

	void Renderer3D::Submit(const Ref<Mesh>& mesh, const glm::mat4& transform)
	{
		const Ref<Shader>& shader = mesh->GetShader();
		shader->Bind();
		shader->SetMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		shader->SetMat4("u_Transform", transform);

		mesh->Bind();
		mesh->Draw();
	}
}
