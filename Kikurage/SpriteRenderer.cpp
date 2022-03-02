#include "SpriteRenderer.h"
#include "Scene.h"

#include "TransformComponent.h"
#include "SpriteComponent.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

SpriteRenderer::SpriteRenderer(Shader shader) {
	this->m_shader = shader;

	auto family = getComponentTypeID<SpriteComponent>();
	m_requiredComponent[family] = true;
	family = getComponentTypeID<TransformComponent>();
	m_requiredComponent[family] = true;
}

SpriteRenderer::~SpriteRenderer() {
	glDeleteVertexArrays(1, &this->m_quadVAO);
}

void SpriteRenderer::init() {
	unsigned int VBO;

	Vertex leftBottom = { glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	Vertex leftTop = { glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 0.0f) };
	Vertex rightBottom = { glm::vec2(0.0f, 1.0f), glm::vec2(0.0f, 1.0f) };
	Vertex rightTop = { glm::vec2(1.0f, 1.0f), glm::vec2(1.0f, 1.0f) };

	vertices[0] = leftBottom;
	vertices[1] = leftTop;
	vertices[2] = rightBottom;
	vertices[3] = rightTop;

	glGenVertexArrays(1, &this->m_quadVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindVertexArray(this->m_quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void SpriteRenderer::update(float dt) {
	
}

void SpriteRenderer::draw() {
	this->m_shader.Use();

	for (auto& e : m_entityArray) {
		//--------------------transformations--------------------//
		glm::mat4 model = glm::mat4(1.0f);
		auto position = parentScene->getComponent<TransformComponent>(e).position;
		auto size = parentScene->getComponent<TransformComponent>(e).size;
		auto rotate = parentScene->getComponent<TransformComponent>(e).rotate;

		// translate
		model = glm::translate(model, glm::vec3(position, 0.0f));
		// rotate
		model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
		model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
		// scale
		model = glm::scale(model, glm::vec3(size, 1.0f));

		this->m_shader.SetMatrix4("model", model);

		//--------------------texture & color--------------------//

		this->m_shader.SetInteger("image", 0);
		glActiveTexture(GL_TEXTURE0);
		parentScene->getComponent<SpriteComponent>(e).texture.Bind();

		this->m_shader.SetVector3f("spriteColor", 
				parentScene->getComponent<SpriteComponent>(e).color);

		glBindVertexArray(this->m_quadVAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.size());
		glBindVertexArray(0);
	}
}