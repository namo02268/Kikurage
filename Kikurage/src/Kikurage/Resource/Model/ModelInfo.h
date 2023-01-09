#pragma once

#include <vector>

#include "Kikurage/Resource/Mesh/Vertex.h"
#include "Kikurage/Resource/Mesh/AABB.h"
#include "OpenGL/Texture2D.h"
#include "Utils/String.h"

namespace Kikurage {
	struct MaterialInfo {
		const char* name;
		const char* DeffuseMapPath{ nullptr };
		const char* SpecularMapPath{ nullptr };
		const char* NormalMapPath{ nullptr };
		const char* HeightMapPath{ nullptr };
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
	};

	struct ModelInfo {
		std::vector<MeshInfo> meshes;
		std::vector<MaterialInfo> materials;
	};
}