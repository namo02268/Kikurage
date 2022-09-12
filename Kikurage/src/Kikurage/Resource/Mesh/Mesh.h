#pragma once

#include "Kikurage/Resource/Mesh/AABB.h"
#include "OpenGL/VertexBuffer.h"
#include "OpenGL/IndexBuffer.h"

class Mesh {
public:
	unsigned int VAO = 0;
	VertexBuffer VBO;
	IndexBuffer IBO;
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
