#pragma once
#include <glm/glm.hpp>

#include "Component.h"

class TransformComponent : public Component {
public:
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 scale = glm::vec3(1.0f);
	glm::vec3 rotation = glm::vec3(0.0f);

public:
	TransformComponent() {}
	TransformComponent(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation)
		: position(position), scale(scale), rotation(rotation) {}
};
