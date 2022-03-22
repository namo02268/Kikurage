#pragma once

#include "Kikurage/ECS/Component.h"
#include "Kikurage/Systems/Collision/Collider.h"


class CollisionComponent : public Component {
public:
	Collider* collider;

public:
	CollisionComponent(Collider* collider) : collider(collider) {}
	~CollisionComponent() { delete collider; }
};
