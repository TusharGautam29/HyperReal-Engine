#pragma once

#include "PerspectiveCamera.h"
#include "Texture.h"
#include <glm/glm.hpp>

namespace HyperR {

	class Renderer3D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const PerspectiveCamera& camera);
		static void EndScene();
		static void Flush();

		// Cube rendering
		static void DrawCube(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color);
		static void DrawCube(const glm::vec3& position, const glm::vec3& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

		// Rotated cube rendering (rotation in degrees)
		static void DrawRotatedCube(const glm::vec3& position, const glm::vec3& size, const glm::vec3& rotation, const glm::vec4& color);
		static void DrawRotatedCube(const glm::vec3& position, const glm::vec3& size, const glm::vec3& rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

		// Advanced: Custom transform matrix
		static void DrawTransformedCube(const glm::mat4& transform, const glm::vec3& size, const glm::vec4& color);

	private:
		// Internal helper methods could go here
	};

}