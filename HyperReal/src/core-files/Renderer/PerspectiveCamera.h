#pragma once

#pragma once

#include <glm/glm.hpp>

namespace HyperR {
	class PerspectiveCamera {
	public:
		PerspectiveCamera(float fovYDegrees, float aspectRatio, float nearClip, float farClip);

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

		const glm::vec3& GetRotation() const { return m_Rotation; }
		void SetRotation(const glm::vec3& rotationEuler) { m_Rotation = rotationEuler; RecalculateViewMatrix(); }

		void SetProjection(float fovYDegrees, float aspectRatio, float nearClip, float farClip);

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	private:
		void RecalculateViewMatrix();

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f }; // Camera world position
		glm::vec3 m_Rotation = { 0.0f, 0.0f, 0.0f }; // Euler angles: pitch (X), yaw (Y), roll (Z)

		float m_FOV = 45.0f;
		float m_AspectRatio = 1.778f; // 16:9 default
		float m_NearClip = 0.1f;
		float m_FarClip = 100.0f;
	};
}
