#pragma once

#include "Kikurage/Resource/Mesh/AABB.h"
#include "OpenGL/VertexBuffer.h"

class Mesh {
public:
	unsigned int VAO = 0;
	VertexBuffer VBO;
	unsigned int EBO = 0;
	const char* path = nullptr;

	unsigned int vertexCount = 0;
	unsigned int indiceCount = 0;

	AABB aabb;

public:
	Mesh();
	Mesh(const Mesh&) = delete;
	Mesh(Mesh&& mesh) noexcept;
	Mesh& operator=(const Mesh& mesh) = delete;
	Mesh& operator=(Mesh&& mesh) noexcept;
	~Mesh();

	void LoadFromFile(const char* path);

private:
	void ClearBuffers();
};
