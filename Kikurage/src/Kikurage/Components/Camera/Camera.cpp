#include "Kikurage/Components/Camera/Camera.h"

namespace Kikurage {
	void Camera::UpdateProjectionMatrix() {
		if (m_orthographic) {
			m_progection = Orthographic(-m_aspectRatio, m_aspectRatio, -1.0f, 1.0f, m_near, m_far);
		}
		else {
			m_progection = Perspective(ToRadians(m_fov), m_aspectRatio, m_near, m_far);
		}
	}

	const Matrix4& Camera::GetProjectionMatrix() const {
		return this->m_progection;
	}

	bool Camera::IsUpdated() const {
		return this->ShouldUpdate;
	}

	float Camera::GetAspectRatio() const {
		return this->m_aspectRatio;
	}

	float Camera::GetFOV() const {
		return this->m_fov;
	}

	float Camera::GetFar() const {
		return this->m_far;
	}

	float Camera::GetNear() const {
		return this->m_near;
	}

	float Camera::GetCameraSpeed() const {
		return this->m_cameraSpeed;
	}

	float Camera::GetMouseSensitivity() const {
		return this->m_mouseSensitivity;
	}

	void Camera::SetAspectRatio(const float ratio) {
		this->m_aspectRatio = ratio;
	}

	void Camera::SetFOV(const float fov) {
		this->m_fov = fov;
	}

	void Camera::SetFar(const float far) {
		this->m_far = far;
	}

	void Camera::SetNear(const float near) {
		this->m_near = near;
	}

	void Camera::SetCameraSpeed(const float speed) {
		this->m_cameraSpeed = speed;
	}

	void Camera::SetMouseSensitivity(const float sensitivity) {
		this->m_mouseSensitivity = sensitivity;
	}
}