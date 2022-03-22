#pragma once
#include <glm/glm.hpp>

#include "Systems/Collision/CollisionPoints.h"
#include "Systems/Collision/SphereCollider.h"
#include "Systems/Collision/PlaneCollider.h"

namespace algo {
	CollisionPoints FindSphereSphereCollisionPoints(
		const SphereCollider* a, const TransformComponent* ta,
		const SphereCollider* b, const TransformComponent* tb)
	{
		glm::vec3 A = a->Center + ta->position;
		glm::vec3 B = b->Center + tb->position;

		float Ar = a->Radius * ta->scale.x;
		float Br = b->Radius * tb->scale.x;

		glm::vec3 AtoB = B - A;
		glm::vec3 BtoA = A - B;

		if (glm::length(AtoB) > Ar + Br) {
			return {
				glm::vec3(0.0f),
				glm::vec3(0.0f),
				glm::vec3(0.0f),
				0,
				false
			};
		}

		A += glm::normalize(AtoB) * Ar;
		B += glm::normalize(BtoA) * Br;

		AtoB = B - A;

		return {
			A, B,
			glm::normalize(AtoB),
			glm::length(AtoB),
			true
		};
	}


	CollisionPoints FindSpherePlaneCollisionPoints(
		const SphereCollider* a, const TransformComponent* ta,
		const PlaneCollider* b, const TransformComponent* tb) 
	{
		glm::vec3 A = a->Center + ta->position;
		// TODO: change to quat
//		glm::vec3 N = glm::normalize(b->Plane * tb->rotation);
		glm::vec3 N = glm::normalize(b->Normal);

		glm::vec3 P = N * b->Distance + tb->position;

		float Ar = a->Radius * ta->scale.x;

		float d = glm::dot((A - P), N);

		if (d > Ar) {
			return {
				glm::vec3(0.0f),
				glm::vec3(0.0f),
				glm::vec3(0.0f),
				0,
				false
			};
		}

		glm::vec3 B = A - N * d;
		A = A - N * Ar;

		return {
			A, B,
			glm::normalize(N),
			glm::length(B - A),
			true
		};

	}
}