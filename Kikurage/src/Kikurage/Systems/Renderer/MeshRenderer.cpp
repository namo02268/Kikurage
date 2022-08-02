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
		auto cTrans = m_parentScene->getComponent<TransformComponent>(e);
		auto cMesh = m_parentScene->getComponent<MeshComponent>(e);
		auto cMat = m_parentScene->getComponent<MaterialComponent>(e);
		auto cParent = m_parentScene->getComponent<Relationship>(e)->parent;

		// material
		this->m_shader->SetVector3f("albedo", cMat->albedo);
		this->m_shader->SetFloat("metallic", cMat->metallic);
		this->m_shader->SetFloat("roughness", cMat->roughness);
		this->m_shader->SetFloat("ao", cMat->ao);

		// model
		this->m_shader->SetMatrix4("model", cTrans->model);
		glBindVertexArray(cMesh->mesh->VAO);
		glDrawElements(GL_TRIANGLES, cMesh->mesh->indiceCount, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}
