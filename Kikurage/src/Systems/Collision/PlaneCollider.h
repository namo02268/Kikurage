#pragma once
#include <glm/glm.hpp>

#include "Systems/Collision/Collider.h"

struct Collider;

struct PlaneCollider : Collider {
	glm::vec3 Normal;
	float Distance;

	PlaneCollider(glm::vec3 Normal, float Distance) : Normal(Normal), Distance(Distance) {}

	CollisionPoints TestCollision(
		const TransformComponent* transform,
		const Collider* collider,
		const TransformComponent* colliderTransform) const override;

	CollisionPoints TestCollision(
		const TransformComponent* transform,
		const SphereCollider* sphere,
		const TransformComponent* sphereTransform) const override;

	CollisionPoints TestCollision(
		const TransformComponent* transform,
		const PlaneCollider* plane,
		const TransformComponent* planeTransform) const override;
};
