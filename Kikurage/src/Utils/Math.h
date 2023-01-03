#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Kikurage {
	using Vector2 = glm::vec2;
	using Vector3 = glm::vec3;
	using Vector4 = glm::vec4;
	using Matrix4 = glm::mat4;
	using Quaternion = glm::quat;

	constexpr Vector3 VectorUp{ 0.0f, 1.0f, 0.0f };
	constexpr Vector3 VectorRight{ 1.0f, 0.0f, 0.0f };
	constexpr Vector3 VectorForward{ 0.0f, 0.0f, 1.0f };
	constexpr Vector3 XAxis{ 1.0f, 0.0f, 0.0f };
	constexpr Vector3 YAxis{ 0.0f, 1.0f, 0.0f };
	constexpr Vector3 ZAxis{ 0.0f, 0.0f, 1.0f };

	inline Quaternion ToQuat(const Matrix4 mat) {
		return glm::toQuat(mat);
	}

	inline Vector3 QuatToEuler(const Quaternion& q) {
		return glm::eulerAngles(q);
	}

	inline Quaternion AngleAxis(float angle, const Vector3& axis) {
		return glm::angleAxis(angle, axis);
	}

	template<typename T>
	inline constexpr T ToDegrees(const T& radians) {
		return glm::degrees(radians);
	}

	template<typename T>
	inline constexpr T ToRadians(const T& degrees) {
		return glm::radians(degrees);
	}

	inline Matrix4 Perspective(float fov, float aspect, float znear, float zfar) {
		return glm::perspective(fov, aspect, znear, zfar);
	}

	inline Matrix4 Orthographic(float left, float right, float bottom, float top, float znear, float zfar) {
		return glm::ortho(left, right, bottom, top, znear, zfar);
	}

	inline Matrix4 ViewMatrix(const Vector3& eye, const Vector3& center, const Vector3& up) {
		return glm::lookAt(eye, center, up);
	}

	template<typename T>
	inline float Dot(const T& v1, const T& v2) {
		return glm::dot(v1, v2);
	}

	inline Vector3 Cross(const Vector3& v1, const Vector3& v2) {
		return glm::cross(v1, v2);
	}

	template<typename T>
	inline T Normalize(const T& value) {
		return glm::normalize(value);
	}

	template<typename T>
	inline auto Length(const T& value) {
		return glm::length(value);
	}

	template<typename T>
	inline auto Length2(const T& value) {
		return glm::length2(value);
	}

	template<typename T>
	inline T Inverse(const T& mat) {
		return glm::inverse(mat);
	}

	inline Matrix4 Translate(const Matrix4& mat, const Vector3& vec) {
		return glm::translate(mat, vec);
	}

	inline Matrix4 Rotate(const Matrix4& mat, float angle, const Vector3& axis) {
		return glm::rotate(mat, angle, axis);
	}

	inline Matrix4 Scale(const Matrix4& mat, const Vector3& vec) {
		return glm::scale(mat, vec);
	}

	inline Vector3 GetNormal(const Vector3& v1, const Vector3& v2, const Vector3& v3) {
		auto temp1 = v2 - v1;
		auto temp2 = v3 - v1;

		return glm::normalize(glm::cross(temp1, temp2));
	}
}
