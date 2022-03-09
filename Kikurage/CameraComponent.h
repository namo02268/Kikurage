#pragma once

#include "Component.h"

class CameraComponent : public Component {
public:
	float Yaw = -90.0f;
	float Pitch = 0.0f;
	float MovementSpeed = 2.5f;
	float MouseSensitivity = 0.1f;
	float Zoom = 45.0f;

	float Near = 0.1f;
	float Far = 200.0f;

	bool constrainPitch = true;

	glm::vec3 Front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
};
