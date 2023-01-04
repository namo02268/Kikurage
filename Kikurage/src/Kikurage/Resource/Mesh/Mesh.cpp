#include "Kikurage/Resource/Mesh/Mesh.h"
#include "Kikurage/Resource/Mesh/MeshLoader.h"

#include <glad/glad.h>

namespace Kikurage {
	Mesh::Mesh() {
	}

	Mesh::Mesh(Mesh&& mesh) noexcept {
		this->VAO = std::move(mesh.VAO);
		this->VBO = std::move(mesh.VBO);
		this->IBO = std::move(mesh.IBO);

		this->path = mesh.path;

		this->vertexCount = mesh.vertexCount;
		this->indiceCount = mesh.indiceCount;
	}

	Mesh& Mesh::operator=(Mesh&& mesh) noexcept {
		this->VAO = std::move(mesh.VAO);
		this->VBO = std::move(mesh.VBO);
		this->IBO = std::move(mesh.IBO);

		this->path = mesh.path;

		this->vertexCount = mesh.vertexCount;
		this->indiceCount = mesh.indiceCount;

		return *this;
	}

	Mesh::~Mesh() {}

	void Mesh::LoadFromFile(const char* path) {
		this->path = path;
		ObjectInfo object = MeshLoader::LoadFromFile(path);
		auto& mesh = object.meshes[0];

		this->vertexCount = mesh.vertices.size();
		this->indiceCount = mesh.indices.size();

		this->aabb = mesh.aabb;

		{
			VAO.Bind();

			VBO.SetData(mesh.vertices.size() * sizeof(Vertex), &mesh.vertices[0], GL_STATIC_DRAW);
			IBO.SetData(mesh.indices.size() * sizeof(unsigned int), &mesh.indices[0], GL_STATIC_DRAW);

			VAO.BindAttribute(0, 3, GL_FLOAT, sizeof(Vertex), 0);
			VAO.BindAttribute(1, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, Normal));
			VAO.BindAttribute(2, 2, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, TexCoords));

			VAO.Unbind();
		}
	}
}
