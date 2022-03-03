#include "MotionSystem.h"
#include "Scene.h"

#include "TransformComponent.h"
#include "MotionComponent.h"

MotionSystem::MotionSystem(){
	auto family = getComponentTypeID<TransformComponent>();
	m_requiredComponent[family] = true;
	family = getComponentTypeID<MotionComponent>();
	m_requiredComponent[family] = true;
}

MotionSystem::~MotionSystem(){

}

void MotionSystem::init() {

}

void MotionSystem::update(float dt) {
	for (auto& e : m_entityArray) {
		m_parentScene->getComponent<TransformComponent>(e).position
			+= m_parentScene->getComponent<MotionComponent>(e).velocity * dt;
		m_parentScene->getComponent<MotionComponent>(e).velocity
			+= m_parentScene->getComponent<MotionComponent>(e).acceleration * dt;
	}
}

void MotionSystem::draw() {

}