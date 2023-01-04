#pragma once

#include "Utils/Math.h"
#include "Kikurage/Systems/Collision/Collider.h"

namespace Kikurage {
	struct Collider;

	struct SphereCollider : Collider {
		Vector3 Center;
		float Radius;

		SphereCollider(Vector3 Center, float Radius) : Center(Center), Radius(Radius) {}

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
