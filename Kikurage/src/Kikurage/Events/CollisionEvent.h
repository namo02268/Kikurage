#pragma once

#include "Kikurage/ECS/Entity.h"
#include "Kikurage/Events/EventBase.h"
#include "Kikurage/Systems/Collision/CollisionPoints.h"

namespace Kikurage {
	struct CollisionEvent : public EventBase {
	public:
		Entity a;
		Entity b;
		CollisionPoints points;

	public:
		CollisionEvent(Entity a, Entity b, CollisionPoints points) : a(a), b(b), points(points) {}
		~CollisionEvent() {}
	};
}
