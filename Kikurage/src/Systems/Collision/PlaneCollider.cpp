#include "Systems/Collision/PlaneCollider.h"
#include "Systems/Collision/SphereCollider.h"

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
	glm::vec3 T = points.A;
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