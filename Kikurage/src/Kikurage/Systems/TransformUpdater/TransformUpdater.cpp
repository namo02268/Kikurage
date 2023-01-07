#include "Kikurage/Systems/TransformUpdater/TransformUpdater.h"
#include "Kikurage/ECS/ECS.h"

#include "Kikurage/Components/Transform/Transform.h"

namespace Kikurage {
	TransformUpdater::TransformUpdater() {
		auto family = getComponentTypeID<Relationship>();
		m_requiredComponent[family] = true;
		family = getComponentTypeID<Transform>();
		m_requiredComponent[family] = true;
	}

	TransformUpdater::~TransformUpdater() {

	}

	void TransformUpdater::Init() {

	}

	void TransformUpdater::Update(float dt) {
		for (auto& e : m_entityArray) {
			auto transform = m_parentScene->GetComponent<Transform>(e);
			auto relation = m_parentScene->GetComponent<Relationship>(e);

			if (transform->IsUpdated()) {
				transform->UpdateLocalMatrix();
			}
			auto parent = relation->parent;
			if (parent) {
				transform->UpdateWorldMatrix(m_parentScene->GetComponent<Transform>(parent)->GetLocalMatrix());
			}
		}
	}

	void TransformUpdater::Draw() {

	}
}