#include "Kikurage/Systems/TransformUpdater/TransformUpdater.h"
#include "Kikurage/Components/Transform/Transform.h"

namespace Kikurage {
	TransformUpdater::TransformUpdater() {
	}

	TransformUpdater::~TransformUpdater() {
	}

	void TransformUpdater::Init() {

	}

	void TransformUpdater::Update(float dt) {
		m_ecs->EachComponent<Transform, Relationship>([&](Transform& transform, Relationship& relation) {
			if (transform.IsUpdated()) {
				transform.UpdateLocalMatrix();
			}
			auto mat = Matrix4{ 1.0f };

			auto parent = relation.parent;
			if (parent) {
				mat = m_ecs->GetComponent<Transform>(parent)->GetLocalMatrix();
			}
			transform.UpdateWorldMatrix(mat);
		});
	}

	void TransformUpdater::Draw() {

	}
}