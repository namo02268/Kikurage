#pragma once

#include "EventHandler.h"
#include "Entity.h"

enum class Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

class CollisionEvent : public Event {
public:
	Entity a;
	Entity b;


public:
	CollisionEvent(Entity a, Entity b) : a(a), b(b) {}
	~CollisionEvent() {}
};