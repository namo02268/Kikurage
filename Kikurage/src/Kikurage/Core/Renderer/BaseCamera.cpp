#include "Kikurage/Core/Renderer/BaseCamera.h"

namespace Kikurage {
	void BaseCamera::UpdateProjectionMatrix() {
		if (m_orthographic) {
			// TODO : Fix SkyBox
			m_projection = Orthographic(-m_aspectRatio, m_aspectRatio, -1.0f, 1.0f, m_near, m_far);
		}
		else {
			m_projection = Perspective(ToRadians(m_fov), m_aspectRatio, m_near, m_far);
		}
	}
}
