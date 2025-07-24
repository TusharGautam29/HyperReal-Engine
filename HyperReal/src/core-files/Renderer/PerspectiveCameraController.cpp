#include "hrpch.h"
#include "PerspectiveCameraController.h"

#include "core-files/Core/Input.h"
#include "core-files/Core/KeyCodes.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <algorithm>

namespace HyperR {

	PerspectiveCameraController::PerspectiveCameraController(float fovYDegrees, float aspectRatio, float nearClip, float farClip)
		: m_FOV(fovYDegrees), m_AspectRatio(aspectRatio), m_NearClip(nearClip), m_FarClip(farClip),
		m_Camera(fovYDegrees, aspectRatio, nearClip, farClip)
	{
		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation({ m_Pitch, m_Yaw, 0.0f });
	}

	void PerspectiveCameraController::OnUpdate(Timestep ts)
	{
		HR_PROFILE_FUNCTION();

		const float velocity = m_MovementSpeed * ts;

		glm::vec3 front;
		front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		front.y = sin(glm::radians(m_Pitch));
		front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		front = glm::normalize(front);

		glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
		glm::vec3 up = glm::normalize(glm::cross(right, front));

		if (Input::IsKeyPressed(HR_KEY_W))
			m_CameraPosition += front * velocity;
		if (Input::IsKeyPressed(HR_KEY_S))
			m_CameraPosition -= front * velocity;
		if (Input::IsKeyPressed(HR_KEY_A))
			m_CameraPosition -= right * velocity;
		if (Input::IsKeyPressed(HR_KEY_D))
			m_CameraPosition += right * velocity;
		if (Input::IsKeyPressed(HR_KEY_E))
			m_CameraPosition += up * velocity;
		if (Input::IsKeyPressed(HR_KEY_Q))
			m_CameraPosition -= up * velocity;

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation({ m_Pitch, m_Yaw, 0.0f }); // No roll
	}

	void PerspectiveCameraController::OnEvent(Event& e)
	{
		HR_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseMovedEvent>(HR_BIND_EVENT_FN(PerspectiveCameraController::OnMouseMoved));
		dispatcher.Dispatch<MouseScrolledEvent>(HR_BIND_EVENT_FN(PerspectiveCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(HR_BIND_EVENT_FN(PerspectiveCameraController::OnWindowResized));
	}

	bool PerspectiveCameraController::OnMouseMoved(MouseMovedEvent& e)
	{
		if (m_FirstMouse)
		{
			m_LastMouseX = e.GetX();
			m_LastMouseY = e.GetY();
			m_FirstMouse = false;
			return false;
		}

		float xOffset = e.GetX() - m_LastMouseX;
		float yOffset = m_LastMouseY - e.GetY(); // reversed: y-coordinates range from bottom to top

		m_LastMouseX = e.GetX();
		m_LastMouseY = e.GetY();

		xOffset *= m_MouseSensitivity;
		yOffset *= m_MouseSensitivity;

		m_Yaw += xOffset;
		m_Pitch += yOffset;

		// Clamp pitch to prevent flipping
		m_Pitch = std::clamp(m_Pitch, -89.0f, 89.0f);

		m_Camera.SetRotation({ m_Pitch, m_Yaw, 0.0f });

		return false;
	}

	bool PerspectiveCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		HR_PROFILE_FUNCTION();

		m_FOV -= e.GetYOffset();
		m_FOV = std::clamp(m_FOV, 10.0f, 90.0f); // Prevent fish-eye or too zoomed-in
		m_Camera.SetProjection(m_FOV, m_AspectRatio, m_NearClip, m_FarClip);
		return false;
	}

	bool PerspectiveCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		HR_PROFILE_FUNCTION();

		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(m_FOV, m_AspectRatio, m_NearClip, m_FarClip);
		return false;
	}

	void PerspectiveCameraController::SetFOV(float fovYDegrees)
	{
		m_FOV = std::clamp(fovYDegrees, 10.0f, 90.0f);
		m_Camera.SetProjection(m_FOV, m_AspectRatio, m_NearClip, m_FarClip);
	}
}
