#include "hrpch.h"
#include "PerspectiveCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace HyperR {

	PerspectiveCamera::PerspectiveCamera(float fovY, float aspectRatio, float nearClip, float farClip)
		: m_FOV(fovY), m_AspectRatio(aspectRatio), m_NearClip(nearClip), m_FarClip(farClip)
	{
		HR_PROFILE_FUNCTION();

		m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);
		m_ProjectionMatrix[1][1] *= -1.0f; // OpenGL flip

		RecalculateViewMatrix();
	}

	void PerspectiveCamera::SetProjection(float fovY, float aspectRatio, float nearClip, float farClip)
	{
		HR_PROFILE_FUNCTION();

		m_FOV = fovY;
		m_AspectRatio = aspectRatio;
		m_NearClip = nearClip;
		m_FarClip = farClip;

		m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);
		m_ProjectionMatrix[1][1] *= -1.0f; // OpenGL flip

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void PerspectiveCamera::RecalculateViewMatrix()
	{
		HR_PROFILE_FUNCTION();

		glm::vec3 front;
		front.x = cos(glm::radians(m_Rotation.y)) * cos(glm::radians(m_Rotation.x));
		front.y = sin(glm::radians(m_Rotation.x));
		front.z = sin(glm::radians(m_Rotation.y)) * cos(glm::radians(m_Rotation.x));
		front = glm::normalize(front);

		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

		m_ViewMatrix = glm::lookAt(m_Position, m_Position + front, up);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}
