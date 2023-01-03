#pragma once

#include "Utils/Math.h"
#include "Kikurage/Systems/Collision/Collider.h"

namespace Kikurage {
	struct Collider;

	struct PlaneCollider : Collider {
		Vector3 Normal;
		float Distance;

		PlaneCollider(Vector3 Normal, float Distance) : Normal(Normal), Distance(Distance) {}

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
}
