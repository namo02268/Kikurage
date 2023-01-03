#pragma once

#include "Kikurage/ECS/Component.h"
#include "Utils/Math.h"

namespace Kikurage {
	struct TransformComponent : public Component {
	public:
		Vector3 position{ 0.0f };
		Vector3 scale{ 0.0f };
		Vector3 rotation{ 0.0f };
		Matrix4 localMatrix{ 1.0f };
		Matrix4 parentMatrix{ 1.0f };
		Matrix4 worldMatrix{ 1.0f };

	public:
		TransformComponent() {}
		TransformComponent(Vector3 position, Vector3 scale, Vector3 rotation)
			: position(position), scale(scale), rotation(rotation) {}
		TransformComponent operator+=(const TransformComponent& rhs) {
			this->position += rhs.position;
			return *this;
		}

		Quaternion GetWorldOrientation() const { return ToQuat(worldMatrix); }
		Quaternion GetLocalOrientation() const { return ToQuat(localMatrix); }

		Vector3 GetUpDirection() const {
			return GetWorldOrientation() * VectorUp;
		}

		Vector3 GetRightDirection() const {
			return GetWorldOrientation() * VectorRight;
		}

		Vector3 GetForwardDirection() const {
			return GetWorldOrientation() * VectorForward;
		}

		void SetRotation(Quaternion q) {
			this->rotation = ToDegrees(QuatToEuler(q));
		}
	};
}
