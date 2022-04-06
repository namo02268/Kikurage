#pragma once

#include "Kikurage/ECS/Entity.h"
#include "Kikurage/Systems/Collision/CollisionPoints.h"

class CollisionEvent : public Event {
public:
	Entity a;
	Entity b;
	CollisionPoints points;

public:
	CollisionEvent(Entity a, Entity b, CollisionPoints points) : a(a), b(b), points(points) {}
	~CollisionEvent() {}
};


