#pragma once

#include "Utils/Math.h"
#include "Kikurage/Components/Transform/Transform.h"

namespace Kikurage {
	class BaseCamera {
	protected:
		Matrix4 m_projection{ 1.0f };
		float m_aspectRatio = 16.0f / 9.0f;
		float m_fov = 45.0f;
		float m_near = 0.1f;
		float m_far = 1000.0f;
		//	float m_zoom = 1.0f;
		bool m_orthographic = false;

		float m_cameraSpeed = 500.0f;
		float m_mouseSensitivity = 0.001f;

		Vector2 m_prevCursorPos{ 0.0f };

	public:
		BaseCamera() = default;
		virtual ~BaseCamera() = default;

		virtual void HandleMouse(Transform& transform, float dt) {}
		virtual void HandleKeyboard(Transform& transform, float dt) {}
		virtual void HandleScroll(Transform& transform, float offset, float dt) {}

		void UpdateProjectionMatrix();
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
