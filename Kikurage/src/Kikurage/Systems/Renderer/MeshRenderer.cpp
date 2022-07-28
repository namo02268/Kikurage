#include "Kikurage/Systems/Renderer/MeshRenderer.h"
#include "Kikurage/ECS/Scene.h"

#include <glm/gtx/quaternion.hpp>

#include "Kikurage/Components/TransformComponent.h"
#include "Kikurage/Components/MeshComponent.h"
#include "Kikurage/Components/MaterialComponent.h"
#include "Kikurage/Components/Relationship.h"

#define Xaxis glm::vec3(1.0, 0.0, 0.0)
#define Yaxis glm::vec3(0.0, 1.0, 0.0)
#define Zaxis glm::vec3(0.0, 0.0, 1.0)

MeshRenderer::MeshRenderer(Shader* shader) {
	this->m_shader = shader;

	auto family = getComponentTypeID<TransformComponent>();
	m_requiredComponent[family] = true;
	family = getComponentTypeID<MeshComponent>();
	m_requiredComponent[family] = true;
	family = getComponentTypeID<MaterialComponent>();
	m_requiredComponent[family] = true;
	family = getComponentTypeID<Relationship>();
	m_requiredComponent[family] = true;
}

MeshRenderer::~MeshRenderer() {

}

void MeshRenderer::init	() {

}

void MeshRenderer::update(float dt) {

}

void MeshRenderer::draw() {
	this->m_shader->Use();
	for (auto& e : m_entityArray) {
		auto trans = m_parentScene->getComponent<TransformComponent>(e);
		auto mesh = m_parentScene->getComponent<MeshComponent>(e);
		auto mat = m_parentScene->getComponent<MaterialComponent>(e);
		auto parent = m_parentScene->getComponent<Relationship>(e)->parent;

		// material
		this->m_shader->SetVector3f("albedo", mat->albedo);
		this->m_shader->SetFloat("metallic", mat->metallic);
		this->m_shader->SetFloat("roughness", mat->roughness);
		this->m_shader->SetFloat("ao", mat->ao);

		// model
		glm::mat4 model = glm::mat4(1.0f);

		if (parent) {
			auto ptrans = m_parentScene->getComponent<TransformComponent>(parent);
			model = glm::translate(model, ptrans->position);
		}

		model = glm::translate(model, trans->position);
		model = glm::rotate(model, glm::radians(trans->rotation.z), Zaxis);
		model = glm::rotate(model, glm::radians(trans->rotation.y), Yaxis);
		model = glm::rotate(model, glm::radians(trans->rotation.x), Xaxis);
		model = glm::scale(model, trans->scale);

		this->m_shader->SetMatrix4("model", model);

		glBindVertexArray(mesh->VAO);
		glDrawElements(GL_TRIANGLES, mesh->mesh->indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}
