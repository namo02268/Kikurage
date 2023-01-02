#include "Kikurage/Core/Renderer/BaseCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Kikurage {
	void BaseCamera::UpdateProjectionMatrix() {
		if (m_orthographic) {
			// TODO : Fix SkyBox
			m_projection = glm::ortho(-m_aspectRatio, m_aspectRatio, -1.0f, 1.0f, m_near, m_far);
		}
		else {
			m_projection = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_near, m_far);
		}
	}
}
