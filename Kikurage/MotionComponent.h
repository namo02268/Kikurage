#pragma once
#include <glm/glm.hpp>

#include "Component.h"

class MotionComponent : public Component {
public:
	glm::vec3 positionVelosity = glm::vec3(0.0f);
	glm::vec3 scaleVelosity = glm::vec3(0.0f);
	glm::vec3 rotationVelosity = glm::vec3(0.0f);

	glm::vec3 positionAcceleration = glm::vec3(0.0f);
	glm::vec3 scaleAcceleration = glm::vec3(0.0f);
	glm::vec3 rotationAcceleration = glm::vec3(0.0f);

public:
	MotionComponent() {}
	MotionComponent(glm::vec3 pVelosity, glm::vec3 sVelosity, glm::vec3 rVelosity, glm::vec3 pAcceleration, glm::vec3 sAcceleration, glm::vec3 rAcceleration)
		: positionVelosity(pVelosity), scaleVelosity(sVelosity), rotationVelosity(rVelosity), positionAcceleration(pAcceleration), scaleAcceleration(sAcceleration), rotationAcceleration(rAcceleration) {}
};