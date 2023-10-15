#include "Kikurage/Systems/Renderer/MeshRenderer.h"

#include "Kikurage/Core/Application/Application.h"
#include "Kikurage/Components/Transform/Transform.h"
#include "Kikurage/Components/Mesh/Mesh.h"
#include "Kikurage/Components/Material/Material.h"

namespace Kikurage {
	MeshRenderer::MeshRenderer() {
	}

	MeshRenderer::~MeshRenderer() {
	}

	void MeshRenderer::Init() {
	}

	void MeshRenderer::Update(float dt) {
	}

	void MeshRenderer::Draw() {
		auto renderer = Application::GetInstance().GetRenderer();

		m_ecs->EachComponent<Transform, Mesh, Material>([&](Transform& transform, Mesh& mesh, Material& material) {
			renderer->DrawObject(mesh, material, transform);
		});
	}
}
