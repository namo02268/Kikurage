#include "Kikurage/Components/Mesh/Mesh.h"

namespace Kikurage {
	void Mesh::CreateBuffers(MeshInfo& meshInfo) {
		this->vertexCount = meshInfo.vertices.size();
		this->indiceCount = meshInfo.indices.size();
		this->aabb = meshInfo.aabb;

		VAO.Bind();

		VBO.SetData(this->vertexCount * sizeof(Vertex), &meshInfo.vertices[0], GL_STATIC_DRAW);
		IBO.SetData(this->indiceCount * sizeof(unsigned int), &meshInfo.indices[0], GL_STATIC_DRAW);

		VAO.BindAttribute(0, 3, GL_FLOAT, sizeof(Vertex), 0);
		VAO.BindAttribute(1, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, Normal));
		VAO.BindAttribute(2, 2, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, TexCoords));

		VAO.Unbind();
	}
}