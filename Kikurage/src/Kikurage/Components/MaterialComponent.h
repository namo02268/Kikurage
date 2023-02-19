#pragma once

#include "Utils/Math.h"
#include "OpenGL/Texture2D.h"

namespace Kikurage {
	struct MaterialComponent {
	public:
		Vector3 albedo{ 1.0f };
		float metallic = 0.0f;
		float roughness = 0.8f;
		float ao = 1.0f;

		Texture2D* DeffuseMap{ nullptr };
		Texture2D* SpecularMap{ nullptr };
		Texture2D* NormalMap{ nullptr };
		Texture2D* HeightMap{ nullptr };

	public:
		MaterialComponent() {}
		MaterialComponent(Vector3 albedo, float metallic, float roughness, float ao)
			: albedo(albedo), metallic(metallic), roughness(roughness), ao(ao) {}

		void SetDeffuseMap(Texture2D* texture) { this->DeffuseMap = texture; }
		void SetSpecularMap(Texture2D* texture) { this->SpecularMap = texture; }
		void SetNormalMap(Texture2D* texture) { this->NormalMap = texture; }
		void SetHeightMap(Texture2D* texture) { this->HeightMap = texture; }
	};
}
