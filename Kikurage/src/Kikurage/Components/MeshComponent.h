#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Kikurage/Resource/Mesh/Mesh.h"
#include "Kikurage/ECS/Component.h"


class MeshComponent : public Component {
public:
	Mesh* mesh;
	unsigned int VAO, VBO, EBO;

public:
	MeshComponent(Mesh* mesh) : mesh(mesh) { setupMesh(); }
	~MeshComponent() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}
	MeshComponent(const MeshComponent&) = delete;
	MeshComponent& operator=(const MeshComponent&) = delete;

	MeshComponent(MeshComponent&& other) noexcept {
		this->mesh = std::move(other.mesh);

		this->VAO = other.VAO;
		other.VAO = 0;
		this->VBO = other.VBO;
		other.VBO = 0;
		this->EBO = other.EBO;
		other.EBO = 0;
	}

	MeshComponent& operator=(MeshComponent&& other) noexcept {
		if (this != &other) {

			this->mesh = std::move(other.mesh);

			this->VAO = other.VAO;
			other.VAO = 0;
			this->VBO = other.VBO;
			other.VBO = 0;
			this->EBO = other.EBO;
			other.EBO = 0;

		}
		return *this;
	}

private:
	void setupMesh() {
		// create buffers/arrays
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, this->mesh->vertices.size() * sizeof(Vertex), &this->mesh->vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->mesh->indices.size() * sizeof(unsigned int), &this->mesh->indices[0], GL_STATIC_DRAW);

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
};
