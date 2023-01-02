#include "Kikurage/Systems/AABBCollision/AABBCollision.h"

#include "Kikurage/ECS/ECS.h"
#include "Kikurage/Components/TransformComponent.h"
#include "Kikurage/Components/MeshComponent.h"
#include "Kikurage/Components/MaterialComponent.h"
#include "Kikurage/Events/CollisionEvent.h"
#include "Kikurage/Core/Event.h"

namespace Kikurage {
	AABBCollision::AABBCollision() {
		auto family = getComponentTypeID<TransformComponent>();
		m_requiredComponent[family] = true;
		family = getComponentTypeID<MeshComponent>();
		m_requiredComponent[family] = true;
	}

	AABBCollision::~AABBCollision() {

	}

	void AABBCollision::Init() {

	}

	void AABBCollision::Update(float dt) {
		for (auto& e : m_entityArray)
			m_parentScene->GetComponent<MaterialComponent>(e)->albedo = glm::vec3(0.0f, 0.0f, 1.0f);

		for (auto& a : m_entityArray) {
			auto aTrans = m_parentScene->GetComponent<TransformComponent>(a);
			auto aMesh = m_parentScene->GetComponent<MeshComponent>(a);
			auto aMat = m_parentScene->GetComponent<MaterialComponent>(a);

			for (auto& b : m_entityArray) {
				if (a == b) break;
				auto bTrans = m_parentScene->GetComponent<TransformComponent>(b);
				auto bMesh = m_parentScene->GetComponent<MeshComponent>(b);
				auto bMat = m_parentScene->GetComponent<MaterialComponent>(b);
				AABB aAABB = { aMesh->mesh->aabb.Min + aTrans->position, aMesh->mesh->aabb.Max + aTrans->position };
				AABB bAABB = { bMesh->mesh->aabb.Min + bTrans->position, bMesh->mesh->aabb.Max + bTrans->position };
				if (this->intersect(aAABB, bAABB)) {
					aMat->albedo = glm::vec3(1.0f, 0.0f, 0.0f);
					bMat->albedo = glm::vec3(1.0f, 0.0f, 0.0f);
				}
			}
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
