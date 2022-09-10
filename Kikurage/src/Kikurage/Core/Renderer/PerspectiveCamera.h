#pragma once

#include <glm/glm.hpp>

// TODO : Add Camera Base Class

struct PerspectiveCamera {
	float Yaw = -90.0f;
	float Pitch = 0.0f;
	float MovementSpeed = 5.0f;
	float MouseSensitivity = 0.1f;
	float Zoom = 45.0f;

	float Near = 0.1f;
	float Far = 1000.0f;

	glm::vec3 position{ 1.0f };

	glm::mat4 projection {1.0f};
	glm::mat4 view{ 1.0f };

	bool constrainPitch = true;

	glm::vec3 Front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
};