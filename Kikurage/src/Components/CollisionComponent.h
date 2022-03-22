#pragma once

#include "ECS/Component.h"
#include "Systems/Collision/Collider.h"


class CollisionComponent : public Component {
public:
	Collider* collider;

public:
	CollisionComponent(Collider* collider) : collider(collider) {}
	~CollisionComponent() { delete collider; }
};
