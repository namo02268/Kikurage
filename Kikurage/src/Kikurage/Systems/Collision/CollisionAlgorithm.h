#pragma once

#include "Kikurage/Systems/Collision/CollisionPoints.h"
#include "Kikurage/Systems/Collision/SphereCollider.h"
#include "Kikurage/Systems/Collision/PlaneCollider.h"
#include "Utils/Math.h"

namespace Kikurage {
	namespace algo {
		CollisionPoints FindSphereSphereCollisionPoints(
			const SphereCollider* a, const TransformComponent* ta,
			const SphereCollider* b, const TransformComponent* tb)
		{
			Vector3 A = a->Center + ta->position;
			Vector3 B = b->Center + tb->position;

			auto Ar = a->Radius * ta->scale.x;
			auto Br = b->Radius * tb->scale.x;

			Vector3 AtoB = B - A;

			if (Length2(AtoB) > (Ar + Br) * (Ar + Br)) {
				return {
					Vector3(0.0f),
					Vector3(0.0f),
					Vector3(0.0f),
					0,
					false
				};
			}

			Vector3 BtoA = A - B;

			A += Normalize(AtoB) * Ar;
			B += Normalize(BtoA) * Br;

			AtoB = B - A;

			return {
				A, B,
				Normalize(AtoB),
				Length(AtoB),
				true
			};
		}


		CollisionPoints FindSpherePlaneCollisionPoints(
			const SphereCollider* a, const TransformComponent* ta,
			const PlaneCollider* b, const TransformComponent* tb)
		{
			Vector3 A = a->Center + ta->position;
			// TODO: change to quat
	//		Vector3 N = Normalize(b->Plane * tb->rotation);
			Vector3 N = Normalize(b->Normal);

			Vector3 P = N * b->Distance + tb->position;

			float Ar = a->Radius * ta->scale.x;

			float d = Dot((A - P), N);

			if (d > Ar) {
				return {
					Vector3(0.0f),
					Vector3(0.0f),
					Vector3(0.0f),
					0,
					false
				};
			}

			Vector3 B = A - N * d;
			A = A - N * Ar;

			return {
				A, B,
				Normalize(N),
				Length(B - A),
				true
			};

		}
	}
}
