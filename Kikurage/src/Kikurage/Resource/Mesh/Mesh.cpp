#include "Kikurage/Resource/Mesh/Mesh.h"
#include "Kikurage/Resource/Mesh/MeshLoader.h"

#include <glad/glad.h>

Mesh::Mesh() {
}

Mesh::Mesh(Mesh&& mesh) noexcept {
	this->VAO = mesh.VAO;
	mesh.VAO = 0;
	this->VBO = mesh.VBO;
	mesh.VBO = 0;
	this->EBO = mesh.EBO;
	mesh.EBO = 0;

	this->path = mesh.path;

	this->vertexCount = mesh.vertexCount;
	this->indiceCount = mesh.indiceCount;
}

Mesh& Mesh::operator=(Mesh&& mesh) noexcept {
	this->VAO = mesh.VAO;
	mesh.VAO = 0;
	this->VBO = mesh.VBO;
	mesh.VBO = 0;
	this->EBO = mesh.EBO;
	mesh.EBO = 0;

	this->path = mesh.path;

	this->vertexCount = mesh.vertexCount;
	this->indiceCount = mesh.indiceCount;

	return *this;
}

Mesh::~Mesh() {
	ClearBuffers();
}

void Mesh::LoadFromFile(const char* path) {
	this->path = path;
	MeshInfo mesh = MeshLoader::LoadFromFile(path);

	this->vertexCount = mesh.vertices.size();
	this->indiceCount = mesh.indices.size();

	{
		// create buffers/arrays
		glGenVertexArrays(1, &this->VAO);
		glGenBuffers(1, &this->VBO);
		glGenBuffers(1, &this->EBO);

		glBindVertexArray(this->VAO);

		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex), &mesh.vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), &mesh.indices[0], GL_STATIC_DRAW);

		// set the vertex attribute pointers
		// positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		// normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
		// texture coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

		glBindVertexArray(0);
	}
}

void Mesh::ClearBuffers() {
	if (this->VAO != 0)
		glDeleteVertexArrays(1, &this->VAO);
	if (this->VBO != 0)
		glDeleteBuffers(1, &this->VBO);
	if (this->EBO != 0)
		glDeleteBuffers(1, &this->EBO);
}