#include "Kikurage/Systems/Collision/SphereCollider.h"
#include "Kikurage/Systems/Collision/CollisionAlgorithm.h"

namespace Kikurage {
	CollisionPoints SphereCollider::TestCollision(
		const Transform* transform,
		const Collider* collider,
		const Transform* colliderTransform) const
	{
		return collider->TestCollision(colliderTransform, this, transform);
	}

	CollisionPoints SphereCollider::TestCollision(
		const Transform* transform,
		const SphereCollider* sphere,
		const Transform* sphereTransform) const
	{
		return algo::FindSphereSphereCollisionPoints(
			this, transform, sphere, sphereTransform);
	}

	CollisionPoints SphereCollider::TestCollision(
		const Transform* transform,
		const PlaneCollider* plane,
		const Transform* planeTransform) const
	{
		return algo::FindSpherePlaneCollisionPoints(
			this, transform, plane, planeTransform);
	}
}
