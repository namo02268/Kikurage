#pragma once

#include "Kikurage/Resource/Mesh/Vertex.h"
#include "Kikurage/Resource/Mesh/AABB.h"

struct MeshInfo {
	const char* name;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	AABB aabb;

	bool hasNormals;
	bool hasTextureCoords;
};

struct ObjectInfo {
	std::vector<MeshInfo> meshes;
};

class MeshLoader {
public:
	static ObjectInfo LoadFromFile(const char* path);
	static void GenerateNormals(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
};
