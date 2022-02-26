#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Component.h"

class TransformComponent : public Component {
public:
	glm::mat4 model;
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;
};
