#include "MotionSystem.h"
#include "Scene.h"

#include "TransformComponent.h"
#include "MotionComponent.h"

MotionSystem::MotionSystem() {
	auto family = getComponentTypeID<TransformComponent>();
	m_requiredComponent[family] = true;
	family = getComponentTypeID<MotionComponent>();
	m_requiredComponent[family] = true;
}

MotionSystem::~MotionSystem() {

}

void MotionSystem::init() {

}

void MotionSystem::update(float dt) {
	for (auto& e : m_entityArray) {
		auto& transfromComponent = m_parentScene->getComponent<TransformComponent>(e);
		auto& motionComponent = m_parentScene->getComponent<MotionComponent>(e);

		transfromComponent.position += motionComponent.positionVelosity * dt;
		transfromComponent.scale += motionComponent.scaleVelosity * dt;
		transfromComponent.rotation += motionComponent.rotationVelosity * dt;

		motionComponent.positionVelosity += motionComponent.positionAcceleration * dt;
		motionComponent.scaleVelosity += motionComponent.scaleAcceleration * dt;
		motionComponent.rotationVelosity += motionComponent.rotationAcceleration * dt;

	}
}

void MotionSystem::draw() {

}