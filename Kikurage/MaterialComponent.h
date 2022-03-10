#pragma once
#include <glm/glm.hpp>

#include "Component.h"

class MaterialComponent : public Component {
public:
	glm::vec3 albedo = glm::vec3(1.0f);
	float metallic = 0.0f;
	float roughness = 0.0f;
	float ao = 1.0f;

public:
	MaterialComponent() {}
	MaterialComponent(glm::vec3 albedo, float metallic, float roughness, float ao)
		: albedo(albedo), metallic(metallic), roughness(roughness), ao(ao) {}
};
