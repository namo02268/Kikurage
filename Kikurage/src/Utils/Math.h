#pragma once

#include <glm/glm.hpp>

inline glm::vec3 GetNormal(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3) {
	auto temp1 = v2 - v1;
	auto temp2 = v3 - v1;

	return glm::normalize(glm::cross(temp1, temp2));
}
