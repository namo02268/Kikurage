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
