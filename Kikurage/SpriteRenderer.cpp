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
//	glDeleteVertexArrays(1, &this->m_quadVAO);
}

void SpriteRenderer::init() {
	for (auto& e : m_entityArray) {
		auto& spriteComponent = m_parentScene->getComponent<SpriteComponent>(e);
		glGenVertexArrays(1, &spriteComponent.VAO);
		glGenBuffers(1, &spriteComponent.VBO);

		glBindBuffer(GL_ARRAY_BUFFER, spriteComponent.VBO);
		glBufferData(GL_ARRAY_BUFFER, spriteComponent.vertices.size() * sizeof(glm::vec2), &spriteComponent.vertices[0], GL_STREAM_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

void SpriteRenderer::update(float dt) {
	
}

void SpriteRenderer::draw() {
	this->m_shader.Use();

	for (auto& e : m_entityArray) {
		auto& transfromComponent = m_parentScene->getComponent<TransformComponent>(e);
		auto& spriteComponent = m_parentScene->getComponent<SpriteComponent>(e);

		//--------------------transformations--------------------//
		glm::mat4 model = glm::mat4(1.0f);
		auto position = transfromComponent.position;
		auto size = transfromComponent.size;
		auto rotate = transfromComponent.rotate;

		// translate
		model = glm::translate(model, glm::vec3(position, 0.0f));
		// rotate
		model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
		model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
		// scale
		model = glm::scale(model, glm::vec3(size, 1.0f));

		this->m_shader.SetMatrix4("model", model);

		//--------------------bind buffers--------------------//
		glBindBuffer(GL_ARRAY_BUFFER, spriteComponent.VBO);
		glBindVertexArray(spriteComponent.VAO);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
		glEnableVertexAttribArray(1);
		int offset = spriteComponent.UVoffset * 4 * sizeof(glm::vec2);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)offset);

		//--------------------texture & color--------------------//
		this->m_shader.SetInteger("image", 0);
		glActiveTexture(GL_TEXTURE0);
		spriteComponent.texture.Bind();
		this->m_shader.SetVector3f("spriteColor", spriteComponent.color);

		//--------------------draw--------------------//
		glBindVertexArray(spriteComponent.VAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		//--------------------bind buffers to default--------------------//
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
}