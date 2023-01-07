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
		AABB aabb;

		bool hasNormals;
		bool hasTextureCoords;
	};

	struct ModelInfo {
		std::vector<MeshInfo> meshes;
	};
}