#pragma once

#include <vector>

#include "Kikurage/Resource/Mesh/Vertex.h"
#include "Kikurage/Resource/Mesh/AABB.h"
#include "OpenGL/Texture2D.h"
#include "Utils/String.h"

namespace Kikurage {
	struct MaterialInfo {
		fixedString<63> name;
		Texture2D* DeffuseMap{ nullptr };
		Texture2D* SpecularMap{ nullptr };
		Texture2D* NormalMap{ nullptr };
		Texture2D* HeightMap{ nullptr };
	};

	struct MeshInfo {
		fixedString<63> name;
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		Vector3 position{ 0.0f };
		AABB aabb;
		MaterialInfo* material;

		bool hasNormals{ false };
		bool hasTextureCoords{ false };
//		bool useTexture{ false }; // TODO
	};

	struct ModelInfo {
		std::vector<MeshInfo> meshes;
		std::vector<MaterialInfo> materials;
	};
}