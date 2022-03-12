#include "Renderer.h"
#include "Scene.h"

#include "TransformComponent.h"
#include "MeshComponent.h"
#include "MaterialComponent.h"

#include <glm/gtx/quaternion.hpp>

#define Xaxis glm::vec3(1.0, 0.0, 0.0)
#define Yaxis glm::vec3(0.0, 1.0, 0.0)
#define Zaxis glm::vec3(0.0, 0.0, 1.0)

Renderer::Renderer(Shader* shader) {
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
	this->m_shader->Use();
	for (auto& e : m_entityArray) {
		auto& transfromComponent = m_parentScene->getComponent<TransformComponent>(e);
		auto& meshComponent = m_parentScene->getComponent<MeshComponent>(e);
		auto& materialComponent = m_parentScene->getComponent<MaterialComponent>(e);

		// material
		this->m_shader->SetVector3f("albedo", materialComponent.albedo);
		this->m_shader->SetFloat("metallic", materialComponent.metallic);
		this->m_shader->SetFloat("roughness", materialComponent.roughness);
		this->m_shader->SetFloat("ao", materialComponent.ao);

		// model
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, transfromComponent.position);
		model = glm::rotate(model, glm::radians(transfromComponent.rotation.z), Zaxis);
		model = glm::rotate(model, glm::radians(transfromComponent.rotation.y), Yaxis);
		model = glm::rotate(model, glm::radians(transfromComponent.rotation.x), Xaxis);
		/*
		glm::vec3 Radians = glm::radians(transfromComponent.rotation) - oldRadians;
		glm::quat q = glm::quat(Radians);
		q = q * oldQuat;
		oldRadians = glm::radians(transfromComponent.rotation);
		oldQuat = glm::quat(oldRadians);
		model *= glm::toMat4(q);
		model *= glm::toMat4(glm::quat(glm::radians(transfromComponent.rotation)));
		*/
		model = glm::scale(model, transfromComponent.scale);

		this->m_shader->SetMatrix4("model", model);

		glBindVertexArray(meshComponent.VAO);
		glDrawElements(GL_TRIANGLES, meshComponent.mesh->indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}
