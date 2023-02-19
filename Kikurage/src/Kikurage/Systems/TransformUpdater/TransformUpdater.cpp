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
		m_ecs->Each<Transform, Relationship>([&](Transform& transform, Relationship& relation) {
			if (transform.IsUpdated()) {
				transform.UpdateLocalMatrix();
			}
			auto parent = relation.parent;
			if (parent) {
				transform.UpdateWorldMatrix(m_ecs->GetComponent<Transform>(parent)->GetLocalMatrix());
			}
		});
	}

	void TransformUpdater::Draw() {

	}
}