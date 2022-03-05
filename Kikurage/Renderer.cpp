#include "Renderer.h"
#include "Scene.h"

#include "TransformComponent.h"
#include "MeshComponent.h"
#include "MaterialComponent.h"

#define Xaxis glm::vec3(1.0, 0.0, 0.0)
#define Yaxis glm::vec3(0.0, 1.0, 0.0)
#define Zaxis glm::vec3(0.0, 0.0, 1.0)

Renderer::Renderer(Shader shader) {
	this->m_shader = shader;

	auto family = getComponentTypeID<TransformComponent>();
	m_requiredComponent[family] = true;
	family = getComponentTypeID<MeshComponent>();
	m_requiredComponent[family] = true;
	family = getComponentTypeID<MaterialComponent>();
	m_requiredComponent[family] = true;
}

Renderer::~Renderer() {

}

void Renderer::init	() {

}

void Renderer::update(float dt) {

}

void Renderer::draw() {
	this->m_shader.Use();
	for (auto& e : m_entityArray) {
		auto& transfromComponent = m_parentScene->getComponent<TransformComponent>(e);
		auto& meshComponent = m_parentScene->getComponent<MeshComponent>(e);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, transfromComponent.position);
		model = glm::rotate(model, glm::radians(transfromComponent.rotation.x), Xaxis);
		model = glm::rotate(model, glm::radians(transfromComponent.rotation.y), Yaxis);
		model = glm::rotate(model, glm::radians(transfromComponent.rotation.z), Zaxis);
		model = glm::scale(model, transfromComponent.scale);

		this->m_shader.SetMatrix4("model", model);

		glBindVertexArray(meshComponent.VAO);
		glDrawElements(GL_TRIANGLES, meshComponent.mesh.indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}