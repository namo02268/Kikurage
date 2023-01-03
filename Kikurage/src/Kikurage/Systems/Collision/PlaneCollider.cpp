#include "Kikurage/Systems/Collision/PlaneCollider.h"
#include "Kikurage/Systems/Collision/SphereCollider.h"

namespace Kikurage {
	CollisionPoints PlaneCollider::TestCollision(
		const TransformComponent* transform,
		const Collider* collider,
		const TransformComponent* colliderTransform) const
	{
		return collider->TestCollision(colliderTransform, this, transform);
	}

	CollisionPoints PlaneCollider::TestCollision(
		const TransformComponent* transform,
		const SphereCollider* sphere,
		const TransformComponent* sphereTransform) const
	{
		CollisionPoints points = sphere->TestCollision(sphereTransform, this, transform);

		// swap
		Vector3 T = points.A;
		points.A = points.B;
		points.B = T;

		points.Normal = -points.Normal;

		return points;
	}

	CollisionPoints PlaneCollider::TestCollision(
		const TransformComponent* transform,
		const PlaneCollider* plane,
		const TransformComponent* planeTransform) const
	{
		return {};
	}
}
