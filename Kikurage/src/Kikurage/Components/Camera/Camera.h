#pragma once

#include "Utils/Math.h"

namespace Kikurage {
	struct Camera
	{
	private:
		Matrix4 m_progection{ 1.0f };
		float m_aspectRatio = 16.0f / 9.0f;
		float m_fov = 45.0f;
		float m_near = 0.1f;
		float m_far = 1000.0f;
		bool m_orthographic = false;
		float m_cameraSpeed = 500.0f;
		float m_mouseSensitivity = 0.001f;
		bool ShouldUpdate = true;

	public:
		void UpdateProjectionMatrix();
		const Matrix4& GetProjectionMatrix() const;
		
		bool IsUpdated() const;

		float GetAspectRatio() const;
		float GetFOV() const;
		float GetFar() const;
		float GetNear() const;
		float GetCameraSpeed() const;
		float GetMouseSensitivity() const;

		void SetAspectRatio(const float ratio);
		void SetFOV(const float fov);
		void SetFar(const float far);
		void SetNear(const float near);
		void SetCameraSpeed(const float speed);
		void SetMouseSensitivity(const float sensitivity);

	};
}
