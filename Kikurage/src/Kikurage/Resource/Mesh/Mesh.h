#pragma once

#include "Kikurage/Resource/Mesh/AABB.h"
#include "OpenGL/VertexArray.h"
#include "OpenGL/VertexBuffer.h"
#include "OpenGL/IndexBuffer.h"

namespace Kikurage {
	class Mesh {
	public:
		VertexArray VAO;
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
	};
}
