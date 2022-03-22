#pragma once

#include "Systems/Collision/CollisionPoints.h"
#include "Components/TransformComponent.h"

struct SphereCollider;
struct PlaneCollider;

struct Collider {
	virtual CollisionPoints TestCollision(
		const TransformComponent* transform,
		const Collider* collider,
		const TransformComponent* colliderTransform) const = 0;

	virtual CollisionPoints TestCollision(
		const TransformComponent* transform,
		const SphereCollider* sphere,
		const TransformComponent* sphereTransform) const = 0;

	virtual CollisionPoints TestCollision(
		const TransformComponent* transform,
		const PlaneCollider* plane,
		const TransformComponent* planeTransform) const = 0;
};


