#pragma once
#include <glm/glm.hpp>

#include "Kikurage/ECS/Component.h"

struct TransformComponent : public Component {
public:
	glm::vec3 position{ 0.0f };
	glm::vec3 scale{ 0.0f };
	glm::vec3 rotation{ 0.0f };
	glm::mat4 model{ 1.0f };

public:
	TransformComponent() {}
	TransformComponent(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation)
		: position(position), scale(scale), rotation(rotation) {}
	TransformComponent operator+=(const TransformComponent& rhs) {
		this->position += rhs.position;
		return *this;
	}
};
