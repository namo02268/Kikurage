#pragma once
#include <glm/glm.hpp>

#include "ECS/Component.h"

class RigidBodyComponent : public Component {
public:
	glm::vec3 velocity = glm::vec3(0.0f);
	glm::vec3 force = glm::vec3(0.0f);

	float mass = 0.1f;
	float restitution = 1.0f;
	float dynamicFriction = 0.1f;
	float staticFriction = 0.2f;

	bool isGravity = false;
	bool isKinematic = false;

public:
	RigidBodyComponent() {}
	RigidBodyComponent(bool isGravity, bool isKinematic) : isGravity(isGravity), isKinematic(isKinematic) {}
};
