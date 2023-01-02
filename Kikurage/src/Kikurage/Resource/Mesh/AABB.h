#pragma once

#include <glm/glm.hpp>

namespace Kikurage {
	class AABB {
	public:
		glm::vec3 Min{ 0.0f };
		glm::vec3 Max{ 0.0f };
	};
}
