#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Component.h"

class MotionComponent : public Component {
public:
	glm::vec2 velocity = glm::vec2(0.0f);
	glm::vec2 acceleration = glm::vec2(0.0f);

public:
	MotionComponent() {}
	MotionComponent(glm::vec2 velocity, glm::vec2 acceleration)
		: velocity(velocity), acceleration(acceleration) {}
};