#include "Kikurage/Systems/Renderer/MeshRenderer.h"
#include "Kikurage/ECS/ECS.h"

#include "Kikurage/Core/Application/Application.h"
#include "Kikurage/Components/Transform/Transform.h"
#include "Kikurage/Components/Mesh/Mesh.h"
#include "Kikurage/Components/MaterialComponent.h"

namespace Kikurage {
	MeshRenderer::MeshRenderer(Shader* shader) {
		this->m_shader = shader;

		auto family = getComponentTypeID<Transform>();
		m_requiredComponent[family] = true;
		family = getComponentTypeID<Mesh>();
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
		auto renderer = Application::GetInstance().GetRenderer();
		for (auto& e : m_entityArray) {
			auto transform = m_ecs->GetComponent<Transform>(e);
			auto mesh = m_ecs->GetComponent<Mesh>(e);
			auto material = m_ecs->GetComponent<MaterialComponent>(e);

			// material
			int textureCount = 0;
			if (material->DeffuseMap != nullptr) {
				glActiveTexture(GL_TEXTURE0 + textureCount);
				m_shader->SetUniform("texture_diffuse", textureCount);
				material->DeffuseMap->Bind();
				textureCount++;
			}

			if (material->SpecularMap != nullptr) {
				glActiveTexture(GL_TEXTURE0 + textureCount);
				m_shader->SetUniform("texture_specular", textureCount);
				material->SpecularMap->Bind();
				textureCount++;
			}


			/*
			this->m_shader->SetUniform("albedo", material->albedo);
			this->m_shader->SetUniform("metallic", material->metallic);
			this->m_shader->SetUniform("roughness", material->roughness);
			this->m_shader->SetUniform("ao", material->ao);
			*/

			// model
			this->m_shader->SetUniform("model", transform->GetWorldMatrix());
			renderer->DrawObject(mesh);
		}
	}
}
