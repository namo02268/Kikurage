#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "Component.h"

struct AABB {
	glm::vec2 min;
	glm::vec2 max;
};

class ColliderComponent : public Component {
public:
	bool doCollision;
	AABB aabb = { glm::vec2(0.0f), glm::vec2(1.0f) };

public:
	ColliderComponent(bool doCollision) : doCollision(doCollision) {}
};