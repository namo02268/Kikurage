#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "Component.h"
#include "Texture2D.h"

class SpriteComponent : public Component {
public:
	unsigned int VAO, VBO;

	std::vector<glm::vec2> vertices;

	int UVoffset = 1;

	Texture2D texture;
	glm::vec3 color = glm::vec3(1.0f);

	int row = 1;
	int column = 1;

public:
	SpriteComponent(Texture2D texture, glm::vec3 color, int row, int column)
		: texture(texture), color(color), row(row), column(column) {

		// position
		vertices = {
			glm::vec2(0.0f, 0.0f),
			glm::vec2(1.0f, 0.0f),
			glm::vec2(0.0f, 1.0f),
			glm::vec2(1.0f, 1.0f),
		};

		// uv
		for (int r = 0; r < this->row; r++) {
			for (int c = 0; c < this->column; c++) {
				std::vector<glm::vec2> uv = {
					glm::vec2(1.0f / column * c      , 1.0f / row * r      ),
					glm::vec2(1.0f / column * (c + 1), 1.0f / row * r      ),
					glm::vec2(1.0f / column * c      , 1.0f / row * (r + 1)),
					glm::vec2(1.0f / column * (c + 1), 1.0f / row * (r + 1))
				};
				vertices.insert(vertices.end(), uv.begin(), uv.end());
			}
		}

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
	}

	~SpriteComponent() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}
};
