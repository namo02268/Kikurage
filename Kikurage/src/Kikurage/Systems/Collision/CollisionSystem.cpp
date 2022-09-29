#include "Kikurage/Systems/Collision/CollisionSystem.h"
#include "Kikurage/ECS/ECS.h"
#include "Kikurage/Events/CollisionEvent.h"

#include "Kikurage/Components/TransformComponent.h"
#include "Kikurage/Components/CollisionComponent.h"
#include "Kikurage/Components/Relationship.h"

#include "Kikurage/Core/Event.h"

CollisionSystem::CollisionSystem() {
	auto family = getComponentTypeID<TransformComponent>();
	m_requiredComponent[family] = true;
	family = getComponentTypeID<CollisionComponent>();
	m_requiredComponent[family] = true;
	family = getComponentTypeID<Relationship>();
	m_requiredComponent[family] = true;
}

CollisionSystem::~CollisionSystem() {

}

void CollisionSystem::Init() {
}

void CollisionSystem::Update(float dt) {
	for (auto& a : m_entityArray) {
		auto a_parent = m_parentScene->GetComponent<Relationship>(a)->parent;
		for (auto& b : m_entityArray) {
			if (a == b) break;

			auto b_parent = m_parentScene->GetComponent<Relationship>(b)->parent;
			auto a_trans = m_parentScene->GetComponent<TransformComponent>(a);
			TransformComponent a_result = *a_trans;
			if (a_parent) {
				a_result += *(m_parentScene->GetComponent<TransformComponent>(a_parent));
			}

			auto b_trans = m_parentScene->GetComponent<TransformComponent>(b);
			TransformComponent b_result = *b_trans;
			if (b_parent) {
				b_result += *(m_parentScene->GetComponent<TransformComponent>(b_parent));
			}

			auto a_col = m_parentScene->GetComponent<CollisionComponent>(a);
			auto b_col = m_parentScene->GetComponent<CollisionComponent>(b);
			CollisionPoints points = a_col->collider->TestCollision(
				&a_result,
				b_col->collider,
				&b_result);
			if (points.HasCollision) {
				CollisionEvent event(a, b, points);
				Event::publish(&event);
			}
		}
	}
}

void CollisionSystem::Draw() {

}