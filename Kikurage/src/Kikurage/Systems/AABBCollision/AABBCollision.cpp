#include "Kikurage/Systems/AABBCollision/AABBCollision.h"

#include "Kikurage/ECS/ECS.h"
#include "Kikurage/Components/Transform.h"
#include "Kikurage/Components/MeshComponent.h"
#include "Kikurage/Components/MaterialComponent.h"
#include "Kikurage/Events/CollisionEvent.h"
#include "Kikurage/Core/Event.h"

namespace Kikurage {
	AABBCollision::AABBCollision() {
		auto family = getComponentTypeID<Transform>();
		m_requiredComponent[family] = true;
		family = getComponentTypeID<ModelComponent>();
		m_requiredComponent[family] = true;
	}

	AABBCollision::~AABBCollision() {

	}

	void AABBCollision::Init() {

	}

	void AABBCollision::Update(float dt) {
		for (auto& e : m_entityArray)
			m_parentScene->GetComponent<MaterialComponent>(e)->albedo = Vector3(0.0f, 0.0f, 1.0f);

		for (auto& a : m_entityArray) {
			auto aTrans = m_parentScene->GetComponent<Transform>(a);
			auto aMesh = m_parentScene->GetComponent<ModelComponent>(a);
			auto aMat = m_parentScene->GetComponent<MaterialComponent>(a);

			/*
			for (auto& b : m_entityArray) {
				if (a == b) break;
				auto bTrans = m_parentScene->GetComponent<Transform>(b);
				auto bMesh = m_parentScene->GetComponent<MeshComponent>(b);
				auto bMat = m_parentScene->GetComponent<MaterialComponent>(b);
				AABB aAABB = { aMesh->mesh->GetAABB().Min + aTrans->GetPosition(), aMesh->mesh->GetAABB().Max + aTrans->GetPosition()};
				AABB bAABB = { bMesh->mesh->GetAABB().Min + bTrans->GetPosition(), bMesh->mesh->GetAABB().Max + bTrans->GetPosition() };
				if (this->intersect(aAABB, bAABB)) {
					aMat->albedo = Vector3(1.0f, 0.0f, 0.0f);
					bMat->albedo = Vector3(1.0f, 0.0f, 0.0f);
				}
			}
			*/
		}
	}

	void AABBCollision::Draw() {

	}

	bool AABBCollision::intersect(AABB& a, AABB& b) {
		return (a.Min.x <= b.Max.x && a.Max.x >= b.Min.x) &&
			(a.Min.y <= b.Max.y && a.Max.y >= b.Min.y) &&
			(a.Min.z <= b.Max.z && a.Max.z >= b.Min.z);
	}
}
