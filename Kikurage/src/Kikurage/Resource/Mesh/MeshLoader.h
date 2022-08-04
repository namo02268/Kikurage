#pragma once

#include "Kikurage/Resource/Mesh/Vertex.h"

struct MeshInfo {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
};

struct ObjectInfo {
	std::vector<MeshInfo> meshes;
};

class MeshLoader {
public:
	static MeshInfo LoadFromFile(const char* path);
};
