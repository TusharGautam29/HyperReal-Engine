#pragma once
#include "core-files/Renderer/OrthographicCamera.h"
#include "Core/Timestep.h"

#include "core-files/Event/KeyEvent.h"
#include "core-files/Event/MouseEvent.h"
#include "core-files/Event/ApplicationEvent.h"

namespace HyperR {
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float AspectRatio, bool rotation = false);

		OrthographicCamera& GetCamera() { return m_Camera; };
		const OrthographicCamera& GetCamera() const { return m_Camera; };
		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;
		bool m_Rotation;
		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
	};

}

