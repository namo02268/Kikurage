#pragma once

#include "Kikurage/Systems/Collision/CollisionPoints.h"
#include "Kikurage/Components/TransformComponent.h"

struct SphereCollider;
struct PlaneCollider;

struct Collider {
	virtual CollisionPoints TestCollision(
		const TransformComponent* transform,
		const Collider* collider,
		const TransformComponent* colliderTransform) const { return{}; }

	virtual CollisionPoints TestCollision(
		const TransformComponent* transform,
		const SphereCollider* sphere,
		const TransformComponent* sphereTransform) const { return{}; }

	virtual CollisionPoints TestCollision(
		const TransformComponent* transform,
		const PlaneCollider* plane,
		const TransformComponent* planeTransform) const { return{}; }
};


