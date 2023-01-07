#pragma once

#include <vector>

#include "Kikurage/Resource/Mesh/Vertex.h"
#include "Kikurage/Resource/Mesh/AABB.h"
#include "Utils/String.h"

namespace Kikurage {
	struct MeshInfo {
		fixedString<63> name;
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		Vector3 position{ 0.0f };
		AABB aabb;

		bool hasNormals{ false };
		bool hasTextureCoords{ false };
	};

	struct ModelInfo {
		std::vector<MeshInfo> meshes;
	};
}