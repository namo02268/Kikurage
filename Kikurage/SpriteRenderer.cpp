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
	float vertices[] = {
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &this->m_quadVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(this->m_quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void SpriteRenderer::update() {
	
}

void SpriteRenderer::draw() {
	this->m_shader.Use();

	for (auto& e : m_entityArray) {
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

		this->m_shader.SetInteger("image", 0);
		glActiveTexture(GL_TEXTURE0);
		parentScene->getComponent<SpriteComponent>(e).texture.Bind();

		glBindVertexArray(this->m_quadVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}
}