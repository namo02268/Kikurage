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
			const Transform* transform,
			const Collider* collider,
			const Transform* colliderTransform) const override;

		CollisionPoints TestCollision(
			const Transform* transform,
			const SphereCollider* sphere,
			const Transform* sphereTransform) const override;

		CollisionPoints TestCollision(
			const Transform* transform,
			const PlaneCollider* plane,
			const Transform* planeTransform) const override;
	};
}
