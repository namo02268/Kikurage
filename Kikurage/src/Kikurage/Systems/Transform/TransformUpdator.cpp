#include "Kikurage/Systems/Transform/TransformUpdator.h"

#include "Kikurage/ECS/ECS.h"
#include "Kikurage/Components/TransformComponent.h"

#include "glm/gtx/transform.hpp"

#define Xaxis glm::vec3(1.0, 0.0, 0.0)
#define Yaxis glm::vec3(0.0, 1.0, 0.0)
#define Zaxis glm::vec3(0.0, 0.0, 1.0)

TransformUpdator::TransformUpdator() {
	auto family = getComponentTypeID<TransformComponent>();
	m_requiredComponent[family] = true;
	family = getComponentTypeID<Relationship>();
	m_requiredComponent[family] = true;
}

void TransformUpdator::init() {

}

void TransformUpdator::update(float dt) {
	for (auto& e : m_entityArray) {
		auto trans = m_parentScene->getComponent<TransformComponent>(e);
		auto parent = m_parentScene->getComponent<Relationship>(e)->parent;

		glm::mat4 buf{ 1.0f };

		if (parent) {
			auto ptrans = m_parentScene->getComponent<TransformComponent>(parent);
			trans->parentMatrix = ptrans->localMatrix;
		}

		buf = glm::translate(buf, trans->position);
		buf = glm::rotate(buf, glm::radians(trans->rotation.z), Zaxis);
		buf = glm::rotate(buf, glm::radians(trans->rotation.y), Yaxis);
		buf = glm::rotate(buf, glm::radians(trans->rotation.x), Xaxis);
		buf = glm::scale(buf, trans->scale);

		trans->localMatrix = buf;
		trans->worldMatrix = trans->parentMatrix * trans->localMatrix;
	}
}

void TransformUpdator::draw() {

}