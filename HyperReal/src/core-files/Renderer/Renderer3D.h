#pragma once

#include "PerspectiveCamera.h"
#include "Mesh.h"

namespace HyperR {

	class Renderer3D {
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const PerspectiveCamera& camera);
		static void EndScene();

		static void Submit(const Ref<Mesh> &mesh, const glm::mat4& transform);

	private:
		struct SceneData {
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}
