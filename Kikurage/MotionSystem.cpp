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
		parentScene->getComponent<TransformComponent>(e).position
			+= parentScene->getComponent<MotionComponent>(e).velocity * dt;
		parentScene->getComponent<MotionComponent>(e).velocity
			+= parentScene->getComponent<MotionComponent>(e).acceleration * dt;
	}
}

void MotionSystem::draw() {

}