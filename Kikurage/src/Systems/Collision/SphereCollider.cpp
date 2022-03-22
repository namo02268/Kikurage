#include "Systems/Collision/SphereCollider.h"
#include "Systems/Collision/CollisionAlgorithm.h"

CollisionPoints SphereCollider::TestCollision(
	const TransformComponent* transform,
	const Collider* collider,
	const TransformComponent* colliderTransform) const
{
	return collider->TestCollision(colliderTransform, this, transform);
}

CollisionPoints SphereCollider::TestCollision(
	const TransformComponent* transform,
	const SphereCollider* sphere,
	const TransformComponent* sphereTransform) const
{
	return algo::FindSphereSphereCollisionPoints(
		this, transform, sphere, sphereTransform);
}

CollisionPoints SphereCollider::TestCollision(
	const TransformComponent* transform,
	const PlaneCollider* plane,
	const TransformComponent* planeTransform) const
{
	return algo::FindSpherePlaneCollisionPoints(
		this, transform, plane, planeTransform);
}