#pragma once

#include "Kikurage/ECS/Component.h"

#include "Kikurage/Resource/Model/ModelInfo.h"
#include "Kikurage/Resource/Mesh/AABB.h"
#include "OpenGL/VertexArray.h"
#include "OpenGL/VertexBuffer.h"
#include "OpenGL/IndexBuffer.h"


namespace Kikurage {
	struct Mesh : public Component {
	private:
		VertexArray VAO;
		VertexBuffer VBO;
		IndexBuffer IBO;

		unsigned int vertexCount = 0;
		unsigned int indiceCount = 0;

		AABB aabb;

	public:
		Mesh() {}
		Mesh(MeshInfo& meshInfo) { this->CreateBuffers(meshInfo); }

		void Bind() const { this->VAO.Bind(); }
		void UnBind() const { this->VAO.Unbind(); }
		unsigned int GetVertexCount() const { return this->vertexCount; }
		unsigned int GetIndiceCount() const { return this->indiceCount; }
		AABB& GetAABB() { return this->aabb; }

		void CreateBuffers(MeshInfo& meshInfo);
	};
}
