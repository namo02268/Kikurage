#pragma once
#include "Utils/Math.h"

#include "Kikurage/ECS/Component.h"

namespace Kikurage {
	struct RigidBodyComponent : public Component {
	public:
		Vector3 velocity{ 0.0f };
		Vector3 force{ 0.0f };

		float mass = 0.1f;
		float restitution = 1.0f;
		float dynamicFriction = 0.1f;
		float staticFriction = 0.2f;

		bool isGravity = false;
		bool isKinematic = false;

	public:
		RigidBodyComponent() {}
		RigidBodyComponent(bool isGravity, bool isKinematic) : isGravity(isGravity), isKinematic(isKinematic) {}
	};
}
