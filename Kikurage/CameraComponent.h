#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Component.h"

class CameraComponent : public Component {
public:
	float size = 4.0f;
};
