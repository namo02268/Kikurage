#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Component.h"

class TransformComponent : public Component {
public:
	glm::vec2 position = glm::vec2(0.0f);
	glm::vec2 size = glm::vec2(1.0f);
	float rotate = 0.0f;

public:
	TransformComponent() {}
	TransformComponent(glm::vec2 position, glm::vec2 size, float rotate)
		: position(position), size(size), rotate(rotate) {}
};
