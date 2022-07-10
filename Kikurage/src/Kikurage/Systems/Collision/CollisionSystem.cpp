#include "Kikurage/Systems/Collision/CollisionSystem.h"
#include "Kikurage/ECS/Scene.h"
#include "Kikurage/Events/CollisionEvent.h"

#include "Kikurage/Components/TransformComponent.h"
#include "Kikurage/Components/CollisionComponent.h"

#include "Kikurage/Core/Application.h"
#include "Kikurage/Core/Event.h"

CollisionSystem::CollisionSystem() {
	auto family = getComponentTypeID<TransformComponent>();
	m_requiredComponent[family] = true;
	family = getComponentTypeID<CollisionComponent>();
	m_requiredComponent[family] = true;
}

CollisionSystem::~CollisionSystem() {

}

void CollisionSystem::init() {
}

void CollisionSystem::update(float dt) {
	for (auto& a : m_entityArray) {
		for (auto& b : m_entityArray) {
			if (a == b)
				break;
			auto a_trans = m_parentScene->getComponent<TransformComponent>(a);
			auto b_trans = m_parentScene->getComponent<TransformComponent>(b);
			auto a_col = m_parentScene->getComponent<CollisionComponent>(a);
			auto b_col = m_parentScene->getComponent<CollisionComponent>(b);
			CollisionPoints points = a_col->collider->TestCollision(
				a_trans,
				b_col->collider,
				b_trans);
			if (points.HasCollision) {
				CollisionEvent event(a, b, points);
				Event::publish(&event);
			}
		}
	}
}

void CollisionSystem::draw() {

}