#pragma once

#include "Utils/Math.h"
#include "Kikurage/ECS/Component.h"

namespace Kikurage {
	struct MaterialComponent : public Component {
	public:
		Vector3 albedo{ 1.0f };
		float metallic = 0.0f;
		float roughness = 0.0f;
		float ao = 1.0f;

	public:
		MaterialComponent() {}
		MaterialComponent(Vector3 albedo, float metallic, float roughness, float ao)
			: albedo(albedo), metallic(metallic), roughness(roughness), ao(ao) {}
	};
}
