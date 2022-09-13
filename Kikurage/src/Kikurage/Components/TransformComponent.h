#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Kikurage/ECS/Component.h"

struct TransformComponent : public Component {
public:
	glm::vec3 position{ 0.0f };
	glm::vec3 scale{ 0.0f };
	glm::vec3 rotation{ 0.0f };
	glm::mat4 localMatrix{ 1.0f };
	glm::mat4 parentMatrix{ 1.0f };
	glm::mat4 worldMatrix{ 1.0f };

public:
	TransformComponent() {}
	TransformComponent(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation)
		: position(position), scale(scale), rotation(rotation) {}
	TransformComponent operator+=(const TransformComponent& rhs) {
		this->position += rhs.position;
		return *this;
	}

	glm::quat GetWorldOrientation() const { return glm::toQuat(worldMatrix); }
	glm::quat GetLocalOrientation() const { return glm::toQuat(localMatrix); }

	glm::vec3 GetUpDirection() const {
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		up = GetWorldOrientation() * up;
		return up;
	}

	glm::vec3 GetRightDirection() const
	{
		glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
		right = GetWorldOrientation() * right;
		return right;
	}

	glm::vec3 GetForwardDirection() const
	{
		glm::vec3 forward = glm::vec3(0.0f, 0.0f, 1.0f);
		forward = GetWorldOrientation() * forward;
		return forward;
	}

	void SetRotation(glm::quat q) {
		this->rotation = glm::degrees(glm::eulerAngles(q));
	}
};
