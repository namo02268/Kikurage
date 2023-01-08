#pragma once

#include "Kikurage/ECS/Component.h"
#include "Utils/Math.h"

namespace Kikurage {
	struct CameraComponent : public Component {
	private:
		Matrix4 m_projection{ 1.0f };
		float m_aspectRatio = 16.0f / 9.0f;
		float m_fov = 45.0f;
		float m_near = 0.1f;
		float m_far = 1000.0f;
		bool m_orthographic = false;
		float m_cameraSpeed = 500.0f;
		float m_mouseSensitivity = 0.001f;
		Vector2 m_prevCursorPos{ 0.0f };
		bool ShouldUpdate = true;

	public:
		void UpdateProjectionMatrix() {
			// TODO : Fix SkyBox
			if (m_orthographic) {
				m_projection = Orthographic(-m_aspectRatio, m_aspectRatio, -1.0f, 1.0f, m_near, m_far);
			}
			else {
				m_projection = Perspective(ToRadians(m_fov), m_aspectRatio, m_near, m_far);
			}
		}

		const Matrix4& GetProjectionMatrix() const { return this->m_projection; }
		float GetAspectRatio() const { return this->m_aspectRatio; }
		float GetFOV() const { return this->m_fov; }
		float GetFar() const { return this->m_far; }
		float GetNear() const { return this->m_near; }
		float GetCameraSpeed() { return this->m_cameraSpeed; }
		float GetMouseSensitivity() const { return this->m_mouseSensitivity; }

		void SetAspectRatio(float ratio) { this->m_aspectRatio = ratio; }
		void SetFOV(float fov) { this->m_fov = fov; }
		void SetFar(float far) { this->m_far = far; }
		void SetNear(float near) { this->m_near = near; }
		void SetCameraSpeed(float cameraSpeed) { this->m_cameraSpeed = cameraSpeed; }
		void SetMouseSensitivity(float value) { this->m_mouseSensitivity = value; }
	};
}
