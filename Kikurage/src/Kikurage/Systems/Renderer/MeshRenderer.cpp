#include "Kikurage/Systems/Renderer/MeshRenderer.h"
#include "Kikurage/ECS/ECS.h"

#include "Kikurage/Core/Application/Application.h"
#include "Kikurage/Components/TransformComponent.h"
#include "Kikurage/Components/MeshComponent.h"
#include "Kikurage/Components/MaterialComponent.h"

namespace Kikurage {
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

	void MeshRenderer::Init() {

	}

	void MeshRenderer::Update(float dt) {

	}

	void MeshRenderer::Draw() {
		this->m_shader->Bind();
		for (auto& e : m_entityArray) {
			auto transform = m_parentScene->GetComponent<TransformComponent>(e);
			auto mesh = m_parentScene->GetComponent<MeshComponent>(e);
			auto material = m_parentScene->GetComponent<MaterialComponent>(e);

			// material
			this->m_shader->SetUniform("albedo", material->albedo);
			this->m_shader->SetUniform("metallic", material->metallic);
			this->m_shader->SetUniform("roughness", material->roughness);
			this->m_shader->SetUniform("ao", material->ao);

			// model
			this->m_shader->SetUniform("model", transform->worldMatrix);
			glBindVertexArray(mesh->mesh->VAO);
			glDrawElements(GL_TRIANGLES, mesh->mesh->indiceCount, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
	}
}
