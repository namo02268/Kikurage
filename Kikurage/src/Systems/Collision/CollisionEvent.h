#pragma once

#include "ECS/EventHandler.h"
#include "ECS/Entity.h"
#include "Systems/Collision/CollisionPoints.h"

class CollisionEvent : public Event {
public:
	Entity a;
	Entity b;
	CollisionPoints points;

public:
	CollisionEvent(Entity a, Entity b, CollisionPoints points) : a(a), b(b), points(points) {}
	~CollisionEvent() {}
};


