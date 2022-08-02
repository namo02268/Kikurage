#pragma once

#include "Kikurage/Resource/Mesh/Vertex.h"

struct MeshInfo {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
};

class MeshLoader {
public:
	static MeshInfo LoadFromFile(const char* path);
};
