#pragma once

#include "RenderCommand.h"
#include "OrthoGraphicCamera.h"
#include "PerspectiveCamera.h"
#include "Shader.h"


namespace HyperR {
	class Renderer {
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void BeginScene(PerspectiveCamera& camera);
		static void EndScene();
		static void Init();
		static void Shutdown();
		static void OnWindowResize(uint32_t width, uint32_t height);

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};
		static SceneData* m_SceneData;
	};
}