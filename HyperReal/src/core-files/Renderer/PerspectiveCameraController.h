#pragma once

#include "PerspectiveCamera.h"
#include "core-files/Core/Timestep.h"

#include "core-files/Event/KeyEvent.h"
#include "core-files/Event/MouseEvent.h"
#include "core-files/Event/ApplicationEvent.h"

namespace HyperR {
	class PerspectiveCameraController
	{
	public:
		PerspectiveCameraController(float fovYDegrees, float aspectRatio, float nearClip = 0.1f, float farClip = 1000.0f);

		PerspectiveCamera& GetCamera() { return m_Camera; }
		const PerspectiveCamera& GetCamera() const { return m_Camera; }

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		void SetMouseSensitivity(float sensitivity) { m_MouseSensitivity = sensitivity; }
		void SetMovementSpeed(float speed) { m_MovementSpeed = speed; }

		float GetFOV() const { return m_FOV; }
		void SetFOV(float fovYDegrees);

	private:
		bool OnMouseMoved(MouseMovedEvent& e);
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		PerspectiveCamera m_Camera;

		float m_FOV;
		float m_AspectRatio;
		float m_NearClip;
		float m_FarClip;

		float m_MovementSpeed = 5.0f;
		float m_MouseSensitivity = 0.1f;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 3.0f };
		float m_Yaw = -90.0f;   // Facing -Z
		float m_Pitch = 0.0f;

		bool m_FirstMouse = true;
		float m_LastMouseX = 0.0f;
		float m_LastMouseY = 0.0f;
	};
}
