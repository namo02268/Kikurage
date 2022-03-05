#include "ColliderSystem.h"
#include "Scene.h"

#include "TransformComponent.h"
#include "ColliderComponent.h"

#include "CollisionEvent.h"

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
	for (auto& a : m_entityArray) {
		auto& aCollider = m_parentScene->getComponent<ColliderComponent>(a);
		if (aCollider.doCollision) {

			for (auto& b : m_entityArray) {
				if (a.GetID() != b.GetID()) {
					auto& bCollider = m_parentScene->getComponent<ColliderComponent>(b);
					auto& aPosition = m_parentScene->getComponent<TransformComponent>(a).position;
					auto& bPosition = m_parentScene->getComponent<TransformComponent>(b).position;

					AABB aAABB = aCollider.aabb;
					AABB bAABB = bCollider.aabb;

					aAABB.max += aPosition;
					aAABB.min += aPosition;
					bAABB.max += bPosition;
					bAABB.min += bPosition;

					if (checkCollision(aAABB, bAABB)) {
						CollisionEvent collisionEvent(a, b);
						m_eventHandler->publish(&collisionEvent);
					}
				}
			}
		}
	}
}

void ColliderSystem::draw() {

}

bool checkCollision(AABB a, AABB b) {
	float d1x = b.min.x - a.max.x;
	float d1y = b.min.y - a.max.y;
	float d2x = a.min.x - b.max.x;
	float d2y = a.min.y - b.max.y;
	if (d1x > 0.0f || d1y > 0.0f)
		return false;

	if (d2x > 0.0f || d2y > 0.0f)
		return false;

	return true;
}