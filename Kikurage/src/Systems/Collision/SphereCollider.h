#pragma once
#include <glm/glm.hpp>

#include "Systems/Collision/Collider.h"

struct Collider;

struct SphereCollider : Collider {
	glm::vec3 Center;
	float Radius;

	SphereCollider(glm::vec3 Center, float Radius) :  Center(Center), Radius(Radius) {}

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
