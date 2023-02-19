#include "Kikurage/Systems/Renderer/MeshRenderer.h"

#include "Kikurage/Core/Application/Application.h"
#include "Kikurage/Components/Transform/Transform.h"
#include "Kikurage/Components/Mesh/Mesh.h"
#include "Kikurage/Components/MaterialComponent.h"

namespace Kikurage {
	MeshRenderer::MeshRenderer(Shader* shader) {
		this->m_shader = shader;
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

		m_ecs->Each<Transform, Mesh, MaterialComponent>([&](Transform& transform, Mesh& mesh, MaterialComponent& material) {
			// material
			int textureCount = 0;
			if (material.DeffuseMap != nullptr) {
				glActiveTexture(GL_TEXTURE0 + textureCount);
				m_shader->SetUniform("texture_diffuse", textureCount);
				material.DeffuseMap->Bind();
				textureCount++;
			}

			if (material.SpecularMap != nullptr) {
				glActiveTexture(GL_TEXTURE0 + textureCount);
				m_shader->SetUniform("texture_specular", textureCount);
				material.SpecularMap->Bind();
				textureCount++;
			}
			// model
			this->m_shader->SetUniform("model", transform.GetWorldMatrix());
			renderer->DrawObject(&mesh);
		});
	}
}
