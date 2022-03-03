#include "ColliderSystem.h"
#include "Scene.h"

#include "TransformComponent.h"
#include "ColliderComponent.h"

bool checkCollision(AABB a, AABB b);

ColliderSystem::ColliderSystem() {
	auto family = getComponentTypeID<TransformComponent>();
	m_requiredComponent[family] = true;
	family = getComponentTypeID<ColliderComponent>();
	m_requiredComponent[family] = true;
}

ColliderSystem::~ColliderSystem() {

}

void ColliderSystem::init() {

}

void ColliderSystem::update(float dt) {
	for (auto& e1 : m_entityArray) {
		auto& e1_colliderComponent = m_parentScene->getComponent<ColliderComponent>(e1);
		if (e1_colliderComponent.doCollision) {
			for (auto& e2 : m_entityArray) {
				if (e1.GetID() != e2.GetID()) {
					auto& e2_colliderComponent = m_parentScene->getComponent<ColliderComponent>(e2);

					auto& e1_aabb = e1_colliderComponent.aabb;
					auto& e2_aabb = e2_colliderComponent.aabb;

					if (checkCollision(e1_aabb, e2_aabb)) {

					}
				}
			}
		}
	}
}

void ColliderSystem::draw() {

}

bool checkCollision(AABB a, AABB b) {
	if (a.max.x < b.min.x ||
		a.min.x < b.max.x) return false;
	if (a.max.y < b.min.y ||
		a.min.y < b.max.y) return false;
	return true;
}