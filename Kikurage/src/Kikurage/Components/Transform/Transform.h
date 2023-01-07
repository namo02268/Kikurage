#pragma once

#include "Kikurage/ECS/Component.h"
#include "Utils/Math.h"

namespace Kikurage {
	struct Transform : public Component {
	private:
		Vector3 position{ 0.0f };
		Vector3 rotation{ 0.0f };
		Vector3 scale{ 1.0f };
		Matrix4 localMatrix{ 1.0f };
		Matrix4 worldMatrix{ 1.0f };
		bool ShouldUpdate = true;

	public:
		Transform() {}
		Transform(Vector3 position, Vector3 scale, Vector3 rotation)
			: position(position), scale(scale), rotation(rotation) {}

		bool operator==(const Transform& other) const {
			return this->position == other.position &&
				this->rotation == other.rotation &&
				this->scale == other.scale;
		}

		bool operator!=(const Transform& other) const {
			return !(*this == other);
		}

		void UpdateLocalMatrix() {
			Matrix4 mat{ 1.0f };
			mat = Kikurage::Translate(mat, this->position);
			mat = Kikurage::Rotate(mat, ToRadians(this->rotation.z), ZAxis);
			mat = Kikurage::Rotate(mat, ToRadians(this->rotation.y), YAxis);
			mat = Kikurage::Rotate(mat, ToRadians(this->rotation.x), XAxis);
			mat = Kikurage::Scale(mat, this->scale);
			this->localMatrix = mat;
			this->ShouldUpdate = false;
		}

		void UpdateWorldMatrix(Matrix4& parent) {
			this->worldMatrix = this->localMatrix * parent;
		}

		bool IsUpdated() { return this->ShouldUpdate; }
		Matrix4& GetLocalMatrix() { return this->localMatrix; }
		Matrix4& GetWorldMatrix() { return this->worldMatrix; }

		Vector3 GetPosition() const { return this->position; }
		Vector3 GetRotation() const { return this->rotation; }
		Quaternion GetQuaternion() const { return ToQuat(ToRotationMatrix(ToRadians(this->rotation))); }
		Vector3 GetScale() const { return this->scale; }

		Vector3 GetUpDirection() const { return GetWorldOrientation() * VectorUp; }
		Vector3 GetRightDirection() const { return GetWorldOrientation() * VectorRight; }
		Vector3 GetForwardDirection() const { return GetWorldOrientation() * VectorForward; }

		Quaternion GetWorldOrientation() const { return ToQuat(localMatrix); }
		Quaternion GetLocalOrientation() const { return ToQuat(localMatrix); }

		void SetPosition(Vector3 position) { this->position = position; this->ShouldUpdate = true; }
		void SetRotation(Vector3 angle) { this->rotation = Vec3fmod(angle + 360.0f, Vector3(360.0f)); this->ShouldUpdate = true; }
		void SetRotation(Quaternion quat) { this->SetRotation(ToDegrees(QuatToEuler(quat))); }
		void SetScale(Vector3 scale) { this->scale = scale; this->ShouldUpdate = true; }
		void SetScale(float scale) { this->SetScale(Vector3(scale)); }

		void Translate(Vector3 dist) { this->position += dist; this->ShouldUpdate = true; }
		void TranslateX(float x) { this->Translate(Vector3(x, 0.0f, 0.0f)); }
		void TranslateY(float y) { this->Translate(Vector3(0.0f, y, 0.0f)); }
		void TranslateZ(float z) { this->Translate(Vector3(0.0f, 0.0f, z)); }

		void Rotate(Vector3 angle) { this->rotation = Vec3fmod(this->rotation + angle + 360.0f, Vector3(360.0f)); this->ShouldUpdate = true; }
		void Rotate(Quaternion quat) { this->Rotate(QuatToEuler(quat)); }
		void RotateX(float x) { this->Rotate(Vector3(x, 0.0f, 0.0f)); }
		void RotateY(float y) { this->Rotate(Vector3(0.0f, y, 0.0f)); }
		void RotateZ(float z) { this->Rotate(Vector3(0.0f, 0.0f, z)); }

		void Scale(Vector3 scale) { this->scale *= scale; this->ShouldUpdate = true; }
		void Scale(float scale) { this->Scale(Vector3(scale)); }
		void ScaleX(float x) { this->Scale(Vector3(x, 0.0f, 0.0f)); }
		void ScaleY(float y) { this->Scale(Vector3(0.0f, y, 0.0f)); }
		void ScaleZ(float z) { this->Scale(Vector3(0.0f, 0.0f, z)); }
	};
}
