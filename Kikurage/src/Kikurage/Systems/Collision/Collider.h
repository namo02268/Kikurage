#pragma once

#include "Kikurage/Systems/Collision/CollisionPoints.h"
#include "Kikurage/Components/Transform.h"

namespace Kikurage {
	struct SphereCollider;
	struct PlaneCollider;

	struct Collider {
		virtual CollisionPoints TestCollision(
			const Transform* transform,
			const Collider* collider,
			const Transform* colliderTransform) const {
			return{};
		}

		virtual CollisionPoints TestCollision(
			const Transform* transform,
			const SphereCollider* sphere,
			const Transform* sphereTransform) const {
			return{};
		}

		virtual CollisionPoints TestCollision(
			const Transform* transform,
			const PlaneCollider* plane,
			const Transform* planeTransform) const {
			return{};
		}
	};
}
