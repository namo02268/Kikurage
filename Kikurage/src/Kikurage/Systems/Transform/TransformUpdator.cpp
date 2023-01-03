#include "Kikurage/Systems/Transform/TransformUpdator.h"

#include "Kikurage/ECS/ECS.h"
#include "Kikurage/Components/TransformComponent.h"

#include "glm/gtx/transform.hpp"

namespace Kikurage {
	TransformUpdator::TransformUpdator() {
		auto family = getComponentTypeID<TransformComponent>();
		m_requiredComponent[family] = true;
		family = getComponentTypeID<Relationship>();
		m_requiredComponent[family] = true;
	}

	void TransformUpdator::Init() {

	}

	void TransformUpdator::Update(float dt) {
		for (auto& e : m_entityArray) {
			auto trans = m_parentScene->GetComponent<TransformComponent>(e);
			auto parent = m_parentScene->GetComponent<Relationship>(e)->parent;

			Matrix4 buf{ 1.0f };

			if (parent) {
				auto ptrans = m_parentScene->GetComponent<TransformComponent>(parent);
				trans->parentMatrix = ptrans->localMatrix;
			}

			buf = Translate(buf, trans->position);
			buf = Rotate(buf, ToRadians(trans->rotation.z), ZAxis);
			buf = Rotate(buf, ToRadians(trans->rotation.y), YAxis);
			buf = Rotate(buf, ToRadians(trans->rotation.x), XAxis);
			buf = Scale(buf, trans->scale);

			trans->localMatrix = buf;
			trans->worldMatrix = trans->parentMatrix * trans->localMatrix;
		}
	}

	void TransformUpdator::Draw() {

	}
}
