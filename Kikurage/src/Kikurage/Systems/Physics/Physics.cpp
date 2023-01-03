#include "Kikurage/Systems/Physics/Physics.h"
#include "Kikurage/ECS/ECS.h"

#include "Kikurage/Components/TransformComponent.h"
#include "Kikurage/Components/RigidBodyComponent.h"
#include "Kikurage/Components/Relationship.h"

#include "Kikurage/Core/Event.h"

namespace Kikurage {
	Physics::Physics() {
		auto family = getComponentTypeID<TransformComponent>();
		m_requiredComponent[family] = true;
		family = getComponentTypeID<RigidBodyComponent>();
		m_requiredComponent[family] = true;
		family = getComponentTypeID<Relationship>();
		m_requiredComponent[family] = true;
	}

	Physics::~Physics() {

	}

	void Physics::Init() {
		Event::subscribe(this, &Physics::onCollisionEvent);
	}

	void Physics::Update(float dt) {
		for (auto& e : m_entityArray) {
			auto transfromComponent = m_parentScene->GetComponent<TransformComponent>(e);
			auto rigidBodyComponent = m_parentScene->GetComponent<RigidBodyComponent>(e);

			if (rigidBodyComponent->isGravity) {
				rigidBodyComponent->force += rigidBodyComponent->mass * m_gravity;
			}

			rigidBodyComponent->velocity += rigidBodyComponent->force / rigidBodyComponent->mass * dt;
			transfromComponent->position += rigidBodyComponent->velocity * dt;

			rigidBodyComponent->force = Vector3(0.0f);
		}
	}

	void Physics::Draw() {

	}

	void Physics::onCollisionEvent(CollisionEvent* collision) {
		auto a_trans = m_parentScene->GetComponent<TransformComponent>(collision->a);
		auto b_trans = m_parentScene->GetComponent<TransformComponent>(collision->b);
		auto a_rigid = m_parentScene->GetComponent<RigidBodyComponent>(collision->a);
		auto b_rigid = m_parentScene->GetComponent<RigidBodyComponent>(collision->b);

		if (a_rigid != nullptr && b_rigid != nullptr) {
			// position solver
			Vector3 resolution = collision->points.B - collision->points.A;

			if (!a_rigid->isKinematic)
				a_trans->position -= resolution;
			if (!b_rigid->isKinematic)
				b_trans->position += resolution;

			// impulse solver
			auto r_velocity = b_rigid->velocity - a_rigid->velocity;
			auto n_velocity = Dot(r_velocity, collision->points.Normal);
			if (std::isnan(n_velocity)) n_velocity = 0.0f;

			if (n_velocity >= 0)
				return;

			auto e = a_rigid->restitution * b_rigid->restitution;
			auto j = -(1.0f + e) * n_velocity / (a_rigid->mass + b_rigid->mass);
			auto impulse = j * collision->points.Normal;

			if (!a_rigid->isKinematic)
				a_rigid->velocity -= impulse * a_rigid->mass;
			if (!b_rigid->isKinematic)
				b_rigid->velocity += impulse * b_rigid->mass;

			// friction solver
			r_velocity = b_rigid->velocity - a_rigid->velocity;
			n_velocity = Dot(r_velocity, collision->points.Normal);
			if (std::isnan(n_velocity)) n_velocity = 0.0f;

			Vector3 tangent = Normalize(r_velocity - n_velocity * collision->points.Normal);
			if (std::isnan(tangent.x) || std::isnan(tangent.y) || std::isnan(tangent.z)) tangent = Vector3(0.0f);
			auto f_velocity = Dot(r_velocity, tangent);
			if (std::isnan(f_velocity)) f_velocity = 0.0f;

			auto mu = Length(Vector2(a_rigid->staticFriction, b_rigid->staticFriction));
			auto f = -f_velocity / (a_rigid->mass + b_rigid->mass);

			Vector3 friction;
			if (std::abs(f) < j * mu) {
				friction = f * tangent;

			}
			else {
				mu = (a_rigid->dynamicFriction + b_rigid->dynamicFriction) / 2;
				friction = -j * tangent * mu;
			}

			if (!a_rigid->isKinematic)
				a_rigid->velocity = a_rigid->velocity - friction * a_rigid->mass;
			if (!b_rigid->isKinematic)
				b_rigid->velocity = b_rigid->velocity + friction * b_rigid->mass;
		}
	}
}
