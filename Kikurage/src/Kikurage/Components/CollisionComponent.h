#pragma once

#include "Kikurage/ECS/Component.h"
#include "Kikurage/Systems/Collision/Collider.h"


class CollisionComponent : public Component {
public:
	Collider* collider = nullptr;

public:
	CollisionComponent(Collider* collider) : collider(collider) {}
	~CollisionComponent() {}

	CollisionComponent(const CollisionComponent&) = delete;
	CollisionComponent& operator=(const CollisionComponent&) = delete;

	CollisionComponent(CollisionComponent&& other) noexcept {
		this->collider = other.collider;
	}

	CollisionComponent& operator=(CollisionComponent&& other) noexcept {
		if (this != &other) {
			this->collider = other.collider;
		}
		return *this;
	}

};
