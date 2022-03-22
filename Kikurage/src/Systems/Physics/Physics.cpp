#include "Systems/Physics/Physics.h"
#include "ECS/Scene.h"

#include "Components/TransformComponent.h"
#include "Components/RigidBodyComponent.h"

Physics::Physics() {
	auto family = getComponentTypeID<TransformComponent>();
	m_requiredComponent[family] = true;
	family = getComponentTypeID<RigidBodyComponent>();
	m_requiredComponent[family] = true;
}

Physics::~Physics() {

}

void Physics::init() {
	m_eventHandler->subscribe(this, &Physics::onCollisionEvent);
}

void Physics::update(float dt) {
	for (auto& e : m_entityArray) {
		auto transfromComponent = m_parentScene->getComponent<TransformComponent>(e);
		auto rigidBodyComponent = m_parentScene->getComponent<RigidBodyComponent>(e);

		if (rigidBodyComponent->isGravity) {
			rigidBodyComponent->force += rigidBodyComponent->mass * m_gravity;
		}

		rigidBodyComponent->velocity += rigidBodyComponent->force / rigidBodyComponent->mass * dt;
		transfromComponent->position += rigidBodyComponent->velocity * dt;

		rigidBodyComponent->force = glm::vec3(0.0f);
	}
}

void Physics::draw() {

}

void Physics::onCollisionEvent(CollisionEvent* collision) {
	auto a_trans = m_parentScene->getComponent<TransformComponent>(collision->a);
	auto b_trans = m_parentScene->getComponent<TransformComponent>(collision->b);
	auto a_rigid = m_parentScene->getComponent<RigidBodyComponent>(collision->a);
	auto b_rigid = m_parentScene->getComponent<RigidBodyComponent>(collision->b);

	if (a_rigid != nullptr && b_rigid != nullptr) {
		// position solver
		glm::vec3 resolution = collision->points.B - collision->points.A;

		if (!a_rigid->isKinematic)
			a_trans->position -= resolution;
		if (!b_rigid->isKinematic)
			b_trans->position += resolution;

		// impulse solver
		auto r_velocity = b_rigid->velocity - a_rigid->velocity;
		auto n_velocity = glm::dot(r_velocity, collision->points.Normal);

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
		n_velocity = glm::dot(r_velocity, collision->points.Normal);

		glm::vec3 tangent = glm::normalize(r_velocity - n_velocity * collision->points.Normal);
		if (std::isnan(tangent.x) || std::isnan(tangent.y) || std::isnan(tangent.z)) tangent = glm::vec3(0.0f);
		auto f_velocity = glm::dot(r_velocity, tangent);

		auto mu = glm::length(glm::vec2(a_rigid->staticFriction, b_rigid->staticFriction));
		auto f = -f_velocity / (a_rigid->mass + b_rigid->mass);

		glm::vec3 friction;
		if (glm::abs(f) < j * mu) {
			friction = f * tangent;

		}
		else {
			mu = glm::length(glm::vec2(a_rigid->dynamicFriction, b_rigid->dynamicFriction));
			friction = -j * tangent * mu;
		}

		if (!a_rigid->isKinematic)
			a_rigid->velocity = a_rigid->velocity - friction * a_rigid->mass;
		if (!b_rigid->isKinematic)
			b_rigid->velocity = b_rigid->velocity + friction * b_rigid->mass;
	}
}