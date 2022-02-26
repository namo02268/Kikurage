#pragma once
#include <vector>
#include <glm/glm.hpp>

struct Vertex {
	// position
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
};

struct Mesh {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
};